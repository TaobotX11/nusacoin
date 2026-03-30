Updated or changed RPC
----------------------

The `bumpfee`, `fundrawtransaction`, `sendmany`, `sendtoaddress`, and `walletcreatefundedpsbt`
RPC commands have been updated to include two new fee estimation methods "NUX/kB" and "nu/B".
The target is the fee expressed explicitly in the given form. Note that use of this feature
will trigger BIP 125 (replace-by-fee) opt-in.

In addition, the `estimate_mode` parameter is now case insensitive for all of the above RPC commands.

The `bumpfee` command now uses `conf_target` rather than `confTarget` in the options.