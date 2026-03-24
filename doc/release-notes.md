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

- `getmempoolinfo` now returns an additional `unbroadcastcount` field. The
  mempool tracks locally submitted transactions until their initial broadcast
  is acknowledged by a peer. This field returns the count of transactions
  waiting for acknowledgement.

- Mempool RPCs such as `getmempoolentry` and `getrawmempool` with
  `verbose=true` now return an additional `unbroadcast` field. This indicates
  whether initial broadcast of the transaction has been acknowledged by a
  peer. `getmempoolancestors` and `getmempooldescendants` are also updated.


Note: some low-level RPC changes mainly useful for testing are described in the
Low-level Changes section below.

GUI changes
-----------

Wallet
------

- To improve wallet privacy, the frequency of wallet rebroadcast attempts is
  reduced from approximately once every 15 minutes to once every 12-36 hours.
  To maintain a similar level of guarantee for initial broadcast of wallet
  transactions, the mempool tracks these transactions as a part of the newly
  introduced unbroadcast set. See the "P2P and network changes" section for
  more information on the unbroadcast set. (#18038)

- The wallet now by default uses bech32 addresses when using RPC, and creates native segwit change outputs.
- The way that output trust was computed has been fixed in #16766, which impacts confirmed/unconfirmed balance status and coin selection

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
