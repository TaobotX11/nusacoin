#!/usr/bin/env python3
# Copyright (c) 2016-2019 The Nusacoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test RPC commands for signing and verifying messages."""

from test_framework.test_framework import NusacoinTestFramework
from test_framework.descriptors import descsum_create
from test_framework.util import assert_equal

class SignMessagesTest(NusacoinTestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 2
        self.extra_args = [["-addresstype=legacy"], []]

    def skip_test_if_missing_module(self):
        self.skip_if_no_wallet()

    def run_test(self):
        message = 'This is just a test message'

        self.log.info('test signing with priv_key')
        priv_key = 'cUeKHd5orzT3mz8P9pxyREHfsWtVfgsfDjiZZBcjUBAaGk1BTj7N'
        address = 'mpLQjfK79b7CCV4VMJWEWAj5Mpx8Up5zxB'
        expected_signature = 'IDf7uPyehTdiy28TFGTlX9J3Bq0vMcCmJoLjSt/I/aTNOSjNI9+dGlkpjM4en7uThGKqTpL80bPUaV9Xy7rbRzE='
        signature = self.nodes[0].signmessagewithprivkey(priv_key, message)
        assert_equal(expected_signature, signature)
        assert self.nodes[0].verifymessage(address, signature, message)

        self.log.info('test signing with an address with wallet')
        address = self.nodes[0].getnewaddress()
        signature = self.nodes[0].signmessage(address, message)
        assert self.nodes[0].verifymessage(address, signature, message)

        self.log.info('test verifying with another address should not work')
        other_address = self.nodes[0].getnewaddress()
        other_signature = self.nodes[0].signmessage(other_address, message)
        assert not self.nodes[0].verifymessage(other_address, signature, message)
        assert not self.nodes[0].verifymessage(address, other_signature, message)

        self.log.info('test signing with a bech32 (P2WPKH) address')
        node1 = self.nodes[1]
        bech32_address = node1.getnewaddress()
        assert bech32_address.startswith('nirt1q')
        bech32_signature = node1.signmessage(bech32_address, message)
        assert node1.verifymessage(bech32_address, bech32_signature, message)
        assert not node1.verifymessage(bech32_address, bech32_signature, 'a different message')

        self.log.info('test the same signature verifies against the legacy form of the key')
        wif = node1.dumpprivkey(bech32_address)
        legacy_desc = node1.getdescriptorinfo('pkh(%s)' % wif)['descriptor']
        legacy_address = node1.deriveaddresses(legacy_desc)[0]
        assert legacy_address[0] in ('m', 'n')
        assert node1.verifymessage(legacy_address, bech32_signature, message)

        self.log.info('test signing from a bech32 address in a wpkh-only descriptor wallet')
        node1.createwallet('wpkhonly', blank=True, descriptors=True)
        wpkh_wallet = node1.get_wallet_rpc('wpkhonly')
        # NB: getdescriptorinfo strips the private key, so checksum the
        # WIF descriptor directly; the import must carry the private key.
        wpkh_desc = descsum_create('wpkh(%s)' % wif)
        assert_equal(wpkh_wallet.importdescriptors([{'desc': wpkh_desc, 'timestamp': 'now'}]), [{'success': True}])
        assert_equal(node1.deriveaddresses(wpkh_desc), [bech32_address])
        wpkh_signature = wpkh_wallet.signmessage(bech32_address, message)
        assert node1.verifymessage(bech32_address, wpkh_signature, message)
        # The legacy form of the same key signs through the wpkh descriptor too.
        wpkh_legacy_signature = wpkh_wallet.signmessage(legacy_address, message)
        assert node1.verifymessage(legacy_address, wpkh_legacy_signature, message)

if __name__ == '__main__':
    SignMessagesTest().main()
