// Copyright (c) 2010-2025 The Nusacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <util/error.h>

#include <tinyformat.h>
#include <util/system.h>
#include <util/translation.h>

bilingual_str TransactionErrorString(const TransactionError err)
{
    switch (err) {
        case TransactionError::OK:
            return Untranslated("No error");
        case TransactionError::MISSING_INPUTS:
            Untranslated("Missing inputs");
        case TransactionError::ALREADY_IN_CHAIN:
            Untranslated("Transaction already in block chain");
        case TransactionError::P2P_DISABLED:
            Untranslated("Peer-to-peer functionality missing or disabled");
        case TransactionError::MEMPOOL_REJECTED:
            Untranslated("Transaction rejected by AcceptToMemoryPool");
        case TransactionError::MEMPOOL_ERROR:
            Untranslated("AcceptToMemoryPool failed");
        case TransactionError::INVALID_PSBT:
            Untranslated("PSBT is not sane");
        case TransactionError::PSBT_MISMATCH:
            Untranslated("PSBTs not compatible (different transactions)");
        case TransactionError::SIGHASH_MISMATCH:
            Untranslated("Specified sighash value does not match existing value");
        case TransactionError::MAX_FEE_EXCEEDED:
            Untranslated("Fee exceeds maximum configured by -maxtxfee");
        // no default case, so the compiler can warn about missing cases
    }
    assert(false);
}

bilingual_str ResolveErrMsg(const std::string& optname, const std::string& strBind)
{
    return strprintf(_("Cannot resolve -%s address: '%s'"), optname, strBind);
}

bilingual_str AmountHighWarn(const std::string& optname)
{
    return strprintf(_("%s is set very high!"), optname);
}

bilingual_str AmountErrMsg(const std::string& optname, const std::string& strValue)
{
    return strprintf(_("Invalid amount for -%s=<amount>: '%s'"), optname, strValue);
}
