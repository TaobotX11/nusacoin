// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2025-2026 The Nusacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <hash.h>            // For CHashWriter
#include <key.h>             // For CKey
#include <key_io.h>          // For DecodeDestination()
#include <pubkey.h>          // For CPubKey
#include <script/standard.h> // For CTxDestination, IsValidDestination(), PKHash
#include <serialize.h>       // For SER_GETHASH
#include <util/message.h>
#include <util/strencodings.h> // For DecodeBase64()

#include <string>
#include <vector>

/**
 * Text used to signify that a signed message follows and to prevent
 * inadvertently signing a transaction.
 */
const std::string MESSAGE_MAGIC = "Nusacoin Signed Message:\n";

MessageVerificationResult MessageVerify(
    const std::string& address,
    const std::string& signature,
    const std::string& message)
{
    CTxDestination destination = DecodeDestination(address);
    if (!IsValidDestination(destination)) {
        return MessageVerificationResult::ERR_INVALID_ADDRESS;
    }

    const PKHash* pkhash = boost::get<PKHash>(&destination);
    const WitnessV0KeyHash* witness_hash = boost::get<WitnessV0KeyHash>(&destination);
    if (pkhash == nullptr && witness_hash == nullptr) {
        return MessageVerificationResult::ERR_ADDRESS_NO_KEY;
    }

    bool invalid = false;
    std::vector<unsigned char> signature_bytes = DecodeBase64(signature.c_str(), &invalid);
    if (invalid) {
        return MessageVerificationResult::ERR_MALFORMED_SIGNATURE;
    }

    CPubKey pubkey;
    if (!pubkey.RecoverCompact(MessageHash(message), signature_bytes)) {
        return MessageVerificationResult::ERR_PUBKEY_NOT_RECOVERED;
    }

    // A P2WPKH address is the hash of the same public key as the
    // corresponding P2PKH address, so compare the recovered key in the
    // destination's own form.
    const CTxDestination recovered_dest = witness_hash ? CTxDestination(WitnessV0KeyHash(pubkey))
                                                       : CTxDestination(PKHash(pubkey));
    if (!(recovered_dest == destination)) {
        return MessageVerificationResult::ERR_NOT_SIGNED;
    }

    return MessageVerificationResult::OK;
}

bool MessageSign(
    const CKey& privkey,
    const std::string& message,
    std::string& signature)
{
    std::vector<unsigned char> signature_bytes;

    if (!privkey.SignCompact(MessageHash(message), signature_bytes)) {
        return false;
    }

    signature = EncodeBase64(signature_bytes);

    return true;
}

uint256 MessageHash(const std::string& message)
{
    CHashWriter hasher(SER_GETHASH, 0);
    hasher << MESSAGE_MAGIC << message;

    return hasher.GetHash();
}

std::string SigningResultString(const SigningResult res)
{
    switch (res) {
        case SigningResult::OK:
            return "No error";
        case SigningResult::PRIVATE_KEY_NOT_AVAILABLE:
            return "Private key not available";
        case SigningResult::SIGNING_FAILED:
            return "Sign failed";
        // no default case, so the compiler can warn about missing cases
    }
    assert(false);
}