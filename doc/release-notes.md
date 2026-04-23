*After branching off for a major version release of Nusacoin Core, use this
template to create the initial release notes draft.*

*The release notes draft is a temporary file that can be added to by anyone. See
[/doc/developer-notes.md#release-notes](/doc/developer-notes.md#release-notes)
for the process.*

*Create the draft, named* "*version* Release Notes Draft"
*(e.g. "0.20.0 Release Notes Draft"), as a collaborative wiki in:*

https://github.com/nusacoin-core/nusacoin-devwiki/wiki/

*Before the final release, move the notes back to this git repository.*

*version* Release Notes Draft
===============================

Nusacoin Core version *version* is now available from:

  <https://nusacoincore.org/bin/nusacoin-core-*version*/>

This release includes new features, various bug fixes and performance
improvements, as well as updated translations.

Please report bugs using the issue tracker at GitHub:

  <https://github.com/nusacoin/nusacoin/issues>

To receive security and update notifications, please subscribe to:

  <https://nusacoincore.org/en/list/announcements/join/>

How to Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over `/Applications/Nusacoin-Qt` (on Mac)
or `nusacoind`/`nusacoin-qt` (on Linux).

Upgrading directly from a version of Nusacoin Core that has reached its EOL is
possible, but it might take some time if the datadir needs to be migrated. Old
wallet versions of Nusacoin Core are generally supported.

Compatibility
==============

Nusacoin Core is supported and extensively tested on operating systems using
the Linux kernel, macOS 10.10+, and Windows 7 and newer. It is not recommended
to use Nusacoin Core on unsupported systems.

Nusacoin Core should also work on most other Unix-like systems but is not
as frequently tested on them.

From Nusacoin Core 0.17.0 onwards, macOS versions earlier than 10.10 are no
longer supported, as Nusacoin Core is now built using Qt 5.9.x which requires
macOS 10.10+. Additionally, Nusacoin Core does not yet change appearance when
macOS "dark mode" is activated.

In addition to previously supported CPU platforms, this release's pre-compiled
distribution provides binaries for the RISC-V platform.

Notable changes
===============

Build System
------------

- OpenSSL is no longer used by Bitcoin Core. The last usage of the library
was removed in #17265.

New RPCs
--------

- The `getindexinfo` RPC returns the actively running indices of the node,
  including their current sync status and height. It also accepts an `index_name`
  to specify returning only the status of that index. (#19550)


New settings
------------

Updated settings
----------------

P2P and network changes
-----------------------

- The mempool now tracks whether transactions submitted via the wallet or RPCs
  have been successfully broadcast. Every 10-15 minutes, the node will try to
  announce unbroadcast transactions until a peer requests it via a `getdata`
  message or the transaction is removed from the mempool for other reasons.
  The node will not track the broadcast status of transactions submitted to the
  node using P2P relay. This version reduces the initial broadcast guarantees
  for wallet transactions submitted via P2P to a node running the wallet. (#18038)

Updated RPCs
------------
- `addmultisigaddress` and `createmultisig` now support up to 20 keys for
  Segwit addresses.

- The `getpeerinfo` RPC returns two new boolean fields, `bip152_hb_to` and
  `bip152_hb_from`, that respectively indicate whether we selected a peer to be
  in compact blocks high-bandwidth mode or whether a peer selected us as a
  compact blocks high-bandwidth peer. High-bandwidth peers send new block
  announcements via a `cmpctblock` message rather than the usual inv/headers
  announcements. See BIP 152 for more details. (#19776)
  
- `getnetworkinfo` now returns two new fields, `connections_in` and
  `connections_out`, that provide the number of inbound and outbound peer
  connections. These new fields are in addition to the existing `connections`
  field, which returns the total number of peer connections. (#19405)

- The `getpeerinfo` RPC now has additional `last_block` and `last_transaction`
  fields that return the UNIX epoch time of the last block and the last valid 
  transaction received from each peer. (#19731)

- `getmempoolinfo` now returns an additional `unbroadcastcount` field. The
  mempool tracks locally submitted transactions until their initial broadcast
  is acknowledged by a peer. This field returns the count of transactions
  waiting for acknowledgement.

- Mempool RPCs such as `getmempoolentry` and `getrawmempool` with
  `verbose=true` now return an additional `unbroadcast` field. This indicates
  whether initial broadcast of the transaction has been acknowledged by a
  peer. `getmempoolancestors` and `getmempooldescendants` are also updated.

- The `getpeerinfo` RPC now returns a `connection_type` field. This indicates
  the type of connection established with the peer. It will return one of six
  options. For more information, see the `getpeerinfo` help documentation.
  (#19725)

- The `getpeerinfo` RPC no longer returns the `addnode` field by default. This
  field will be fully removed in the next major release.  It can be accessed
  with the configuration option `-deprecatedrpc=getpeerinfo_addnode`. However,
  it is recommended to instead use the `connection_type` field (it will return
  `manual` when addnode is true). (#19725)

## CLI

- The `connections` field of `bitcoin-cli -getinfo` is expanded to return a JSON
  object with `in`, `out` and `total` numbers of peer connections. It previously
  returned a single integer value for the total number of peer connections. (#19405)

Note: some low-level RPC changes mainly useful for testing are described in the
Low-level Changes section below.

GUI changes
-----------

Wallet
------
- We now support up to 20 keys in `multi()` and `sortedmulti()` descriptors
  under `wsh()`. (#20867)

- A new `listdescriptors` RPC is available to inspect the contents of descriptor-enabled wallets.
  The RPC returns public versions of all imported descriptors, including their timestamp and flags.
  For ranged descriptors, it also returns the range boundaries and the next index to generate addresses from. (#20226)

- To improve wallet privacy, the frequency of wallet rebroadcast attempts is
  reduced from approximately once every 15 minutes to once every 12-36 hours.
  To maintain a similar level of guarantee for initial broadcast of wallet
  transactions, the mempool tracks these transactions as a part of the newly
  introduced unbroadcast set. See the "P2P and network changes" section for
  more information on the unbroadcast set. (#18038)
- [doc / test / mempool] unbroadcast follow-ups #18807

- The wallet now by default uses bech32 addresses when using RPC, and creates native segwit change outputs.
- The way that output trust was computed has been fixed in #16766, which impacts confirmed/unconfirmed balance status and coin selection

Notification changes
--------------------

`-walletnotify` notifications are now sent for wallet transactions that are
removed from the mempool because they conflict with a new block. These
notifications were sent previously before the v0.19 release, but had been
broken since that release (bug
[#18325](https://github.com/bitcoin/bitcoin/issues/18325)).

Low-level changes
=================

- The RPC gettransaction, listtransactions and listsinceblock responses now also
includes the height of the block that contains the wallet transaction, if any.

Command line
------------

Command line options prefixed with main/test/regtest network names like
`-main.port=8333` `-test.server=1` previously were allowed but ignored. Now
they trigger "Invalid parameter" errors on startup.

Tests
-----

- `-fallbackfee` was 0 (disabled) by default for the main chain, but 0.0002 by default for the test chains. Now it is 0
  by default for all chains. Testnet and regtest users will have to add `fallbackfee=0.0002` to their configuration if
  they weren't setting it and they want it to keep working like before. (#16524)

Credits
=======

Thanks to everyone who directly contributed to this release:


As well as to everyone that helped with translations on
[Transifex](https://www.transifex.com/nusacoin/nusacoin/).
