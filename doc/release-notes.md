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

From Nusacoin Core 26.30.0 onwards, macOS versions earlier than 10.10 are no
longer supported, as Nusacoin Core is now built using Qt 5.9.x which requires
macOS 10.10+. Additionally, Nusacoin Core does not yet change appearance when
macOS "dark mode" is activated.

In addition to previously supported CPU platforms, this release's pre-compiled
distribution provides binaries for the RISC-V platform.

Notable changes
===============
The node's known peers are persisted to disk in a file called `peers.dat`. The
format of this file has been changed in a backwards-incompatible way in order to
accommodate the storage of Tor v3 and other BIP155 addresses. This means that if
the file is modified by 0.26.60 or newer then older versions will not be able to
read it. Those old versions, in the event of a downgrade, will log an error
message that deserialization has failed and will continue normal operation
as if the file was missing, creating a new empty one. (#19954) 


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
- Passing an invalid `-rpcauth` argument now cause bitcoind to fail to start.  (#20461)

- Netmasks that contain 1-bits after 0-bits (the 1-bits are not contiguous on
  the left side, e.g. 255.0.255.255) are no longer accepted. They are invalid
  according to RFC 4632.

- A `download` permission has been extracted from the `noban` permission. For
  compatibility, `noban` implies the `download` permission, but this may change
  in future releases. Refer to the help of the affected settings `-whitebind`
  and `-whitelist` for more details. (#19191)


P2P and network changes
-----------------------

- The mempool now tracks whether transactions submitted via the wallet or RPCs
  have been successfully broadcast. Every 10-15 minutes, the node will try to
  announce unbroadcast transactions until a peer requests it via a `getdata`
  message or the transaction is removed from the mempool for other reasons.
  The node will not track the broadcast status of transactions submitted to the
  node using P2P relay. This version reduces the initial broadcast guarantees
  for wallet transactions submitted via P2P to a node running the wallet. (#18038)

#### Changes regarding misbehaving peers

Peers that misbehave (e.g. send us invalid blocks) are now referred to as
discouraged nodes in log output, as they're not (and weren't) strictly banned:
incoming connections are still allowed from them, but they're preferred for
eviction.

Furthermore, a few additional changes are introduced to how discouraged
addresses are treated:

- Discouraging an address does not time out automatically after 24 hours
  (or the `-bantime` setting). Depending on traffic from other peers,
  discouragement may time out at an indeterminate time.

- Discouragement is not persisted over restarts.

- There is no method to list discouraged addresses. They are not returned by
  the `listbanned` RPC. That RPC also no longer reports the `ban_reason`
  field, as `"manually added"` is the only remaining option.

- Discouragement cannot be removed with the `setban remove` RPC command.
  If you need to remove a discouragement, you can remove all discouragements by
  stop-starting your node.

- The Tor onion service that is automatically created by setting the
  `-listenonion` configuration parameter will now be created as a Tor v3 service
  instead of Tor v2. The private key that was used for Tor v2 (if any) will be
  left untouched in the `onion_private_key` file in the data directory (see
  `-datadir`) and can be removed if not needed. Bitcoin Core will no longer
  attempt to read it. The private key for the Tor v3 service will be saved in a
  file named `onion_v3_private_key`. To use the deprecated Tor v2 service (not
  recommended), then `onion_private_key` can be copied over
  `onion_v3_private_key`, e.g.
  `cp -f onion_private_key onion_v3_private_key`. (#19954)

Updated RPCs
------------

  The RPCs which accept descriptors now accept the new sortedmulti(...) descriptor type which supports multisig scripts where the public keys are sorted lexicographically in the resulting script. (#17056)

  The walletprocesspsbt and walletcreatefundedpsbt RPCs now include BIP32 derivation paths by default for public keys if we know them. This can be disabled by setting the bip32derivs parameter to false. (#17264)

  The bumpfee RPC's parameter totalFee, which was deprecated in 0.19, has been removed. (#18312)

  The bumpfee RPC will return a PSBT when used with wallets that have private keys disabled. (#16373)

  The getpeerinfo RPC now includes a mapped_as field to indicate the mapped Autonomous System used for diversifying peer selection. See the -asmap configuration option described below in New Settings. (#16702)

  The createmultisig and addmultisigaddress RPCs now return an output script descriptor for the newly created address. (#18032)

- `walletprocesspsbt` and `walletcreatefundedpsbt` now include BIP 32 derivation paths by default for public keys if we know them. This can be disabled by setting `bip32derivs` to `false`.

- `addmultisigaddress` and `createmultisig` now support up to 20 keys for
  Segwit addresses.

- The `getpeerinfo` RPC returns two new boolean fields, `bip152_hb_to` and
  `bip152_hb_from`, that respectively indicate whether we selected a peer to be
  in compact blocks high-bandwidth mode or whether a peer selected us as a
  compact blocks high-bandwidth peer. High-bandwidth peers send new block
  announcements via a `cmpctblock` message rather than the usual inv/headers
  announcements. See BIP 152 for more details. (#19776)

- The `getpeerinfo` RPC no longer returns the `banscore` field unless the configuration
  option `-deprecatedrpc=banscore` is used. The `banscore` field will be fully
  removed in the next major release. (#19469)


- The `-banscore` configuration option, which modified the default threshold for
  disconnecting and discouraging misbehaving peers, has been removed as part of
  changes in 0.20.1 and in this release to the handling of misbehaving peers.
  Refer to "Changes regarding misbehaving peers" in the 0.20.1 release notes for
  details. (#19464)
  
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

- The `testmempoolaccept` RPC returns `vsize` and a `fee` object with the `base` fee
  if the transaction passes validation. (#19940)

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
- The "Start Nusacoin Core on system login" option has been removed on macOS.

- #277 Do not use QClipboard::Selection on Windows and macOS.
- #280 Remove user input from URI error message
- #365 Draw "eye" sign at the beginning of watch-only addresses


Wallet
------
### Experimental Descriptor Wallets

Please note that Descriptor Wallets are still experimental and not all expected functionality
is available. Additionally there may be some bugs and current functions may change in the future.
Bugs and missing functionality can be reported to the [issue tracker](https://github.com/Nusacoin/Nusacoin/issues).

0.26.40 introduces a new type of wallet - Descriptor Wallets. Descriptor Wallets store
scriptPubKey information using descriptors. This is in contrast to the Legacy Wallet
structure where keys are used to generate scriptPubKeys and addresses. Because of this
shift to being script based instead of key based, many of the confusing things that Legacy
Wallets do are not possible with Descriptor Wallets. Descriptor Wallets use a definition
of "mine" for scripts which is simpler and more intuitive than that used by Legacy Wallets.
Descriptor Wallets also uses different semantics for watch-only things and imports.

As Descriptor Wallets are a new type of wallet, their introduction does not affect existing wallets.
Users who already have a Nusacoin Core wallet can continue to use it as they did before without
any change in behavior. Newly created Legacy Wallets (which is the default type of wallet) will
behave as they did in previous versions of Nusacoin Core.

The differences between Descriptor Wallets and Legacy Wallets are largely limited to non user facing
things. They are intended to behave similarly except for the import/export and watchonly functionality
as described below.

#### Creating Descriptor Wallets

Descriptor Wallets are not created by default. They must be explicitly created using the
`createwallet` RPC or via the GUI. A `descriptors` option has been added to `createwallet`.
Setting `descriptors` to `true` will create a Descriptor Wallet instead of a Legacy Wallet.

In the GUI, a checkbox has been added to the Create Wallet Dialog to indicate that a
Descriptor Wallet should be created.

Without those options being set, a Legacy Wallet will be created instead. Additionally the
Default Wallet created upon first startup of Nusacoin Core will be a Legacy Wallet.

#### `IsMine` Semantics

`IsMine` refers to the function used to determine whether a script belongs to the wallet.
This is used to determine whether an output belongs to the wallet. `IsMine` in Legacy Wallets
returns true if the wallet would be able to sign an input that spends an output with that script.
Since keys can be involved in a variety of different scripts, this definition for `IsMine` can
lead to many unexpected scripts being considered part of the wallet.

With Descriptor Wallets, descriptors explicitly specify the set of scripts that are owned by
the wallet. Since descriptors are deterministic and easily enumerable, users will know exactly
what scripts the wallet will consider to belong to it. Additionally the implementation of `IsMine`
in Descriptor Wallets is far simpler than for Legacy Wallets. Notably, in Legacy Wallets, `IsMine`
allowed for users to take one type of address (e.g. P2PKH), mutate it into another address type
(e.g. P2WPKH), and the wallet would still detect outputs sending to the new address type
even without that address being requested from the wallet. Descriptor Wallets does not
allow for this and will only watch for the addresses that were explicitly requested from the wallet.

These changes to `IsMine` will make it easier to reason about what scripts the wallet will
actually be watching for in outputs. However for the vast majority of users, this change is
largely transparent and will not have noticeable effect.

#### Imports and Exports

In Legacy Wallets, raw scripts and keys could be imported to the wallet. Those imported scripts
and keys are treated separately from the keys generated by the wallet. This complicates the `IsMine`
logic as it has to distinguish between spendable and watchonly.

Descriptor Wallets handle importing scripts and keys differently. Only complete descriptors can be
imported. These descriptors are then added to the wallet as if it were a descriptor generated by
the wallet itself. This simplifies the `IsMine` logic so that it no longer has to distinguish
between spendable and watchonly. As such, the watchonly model for Descriptor Wallets is also
different and described in more detail in the next section.

To import into a Descriptor Wallet, a new `importdescriptors` RPC has been added that uses a syntax
similar to that of `importmulti`.

As Legacy Wallets and Descriptor Wallets use different mechanisms for storing and importing scripts and keys
the existing import RPCs have been disabled for descriptor wallets.
New export RPCs for Descriptor Wallets have not yet been added.

The following RPCs are disabled for Descriptor Wallets:

* importprivkey
* importpubkey
* importaddress
* importwallet
* dumpprivkey
* dumpwallet
* importmulti
* addmultisigaddress
* sethdseed

#### Watchonly Wallets

A Legacy Wallet contains both private keys and scripts that were being watched.
Those watched scripts would not contribute to your normal balance. In order to see the watchonly
balance and to use watchonly things in transactions, an `include_watchonly` option was added
to many RPCs that would allow users to do that. However it is easy to forget to include this option.

Descriptor Wallets move to a per-wallet watchonly model. Instead an entire wallet is considered to be
watchonly depending on whether it was created with private keys disabled. This eliminates the need
to distinguish between things that are watchonly and things that are not within a wallet itself.

This change does have a caveat. If a Descriptor Wallet with private keys *enabled* has
a multiple key descriptor without all of the private keys (e.g. `multi(...)` with only one private key),
then the wallet will fail to sign and broadcast transactions. Such wallets would need to use the PSBT
workflow but the typical GUI Send, `sendtoaddress`, etc. workflows would still be available, just
non-functional.

This issue is worsened if the wallet contains both single key (e.g. `wpkh(...)`) descriptors and such
multiple key descriptors as some transactions could be signed and broadast and others not. This is
due to some transactions containing only single key inputs, while others would contain both single
key and multiple key inputs, depending on which are available and how the coin selection algorithm
selects inputs. However this is not considered to be a supported use case; multisigs
should be in their own wallets which do not already have descriptors. Although users cannot export
descriptors with private keys for now as explained earlier.

#### BIP 44/49/84 Support

The change to using descriptors changes the default derivation paths used by Nusacoin Core
to adhere to BIP 44/49/84. Descriptors with different derivation paths can be imported without
issue.

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

- The `-zapwallettxes` startup option has been removed and its functionality removed from the wallet.
  This option was originally intended to allow for the fee bumping of transactions that did not
  signal RBF. This functionality has been superseded with the abandon transaction feature.

  Nusacoin Core will no longer create an unnamed `""` wallet by default when no wallet is specified on the command line or in the configuration files. 
  For backwards compatibility, if an unnamed `""` wallet already exists and would have been loaded previously, then it will still be loaded.
  Users without an unnamed `""` wallet and without any other wallets to be loaded on startup  will be prompted to either choose a wallet to load, or to create a new wallet.

The `-salvagewallet` startup option has been removed. A new `salvage` command has been added to the `nusacoin-wallet` tool which performs the salvage operations that `-salvagewallet` did.

Configuration
-------------

Wallets created or loaded in the GUI will now be automatically loaded on
startup, so they don't need to be manually reloaded next time Nusacoin is
started. The list of wallets to load on startup is stored in
`\<datadir\>/settings.json` and augments any command line or `nusacoin.conf`
`-wallet=` settings that specify more wallets to load. Wallets that are
unloaded in the GUI get removed from the settings list so they won't load again
automatically next startup. (#19754)

The `createwallet`, `loadwallet`, and `unloadwallet` RPCs now accept
`load_on_startup` options to modify the settings list. Unless these options are
explicitly set to true or false, the list is not modified, so the RPC methods
remain backwards compatible. (#15937)

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
`-main.port=28573` `-test.server=1` previously were allowed but ignored. Now
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
