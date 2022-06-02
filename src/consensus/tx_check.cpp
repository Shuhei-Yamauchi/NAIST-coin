// Copyright (c) 2017-2021 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <consensus/tx_check.h>

#include <consensus/amount.h>
#include <primitives/transaction.h>
#include <consensus/validation.h>
#include <iostream>

bool CheckTransaction(const CTransaction& tx, TxValidationState& state)
{
    
    //std::cout << "[IsFinalTx]address_to_is  " + tx. + "\n";
    std::cout << "[IsFinalTx]address_from_is " + tx.address_from + "\n";

    if(tx.accountMessage != NULL){
       // std::string str(tx.accountMessage);
        //std::cout << str + "\n";
       // std::string str = tx.accountMessage;
    }

    
//std::cout << "dummy^CTxIN is " + std::to_string(tx.vin[0].dummy_CTxIn);


// if(tx.address_from == NULL){
//      std::cout << "[IsFinalTx]address_from_is " + tx.address_from + "\n";
// }

    // if(tx.transactionType == "account"){
    // int ret = 0;
	// unsigned char digest[SHA256_DIGEST_LENGTH];
	// SHA256_CTX sha_ctx;
	// SHA256_Init(&sha_ctx); // コンテキストを初期化
	// SHA256_Update(&sha_ctx, tx.accountMessage, sizeof(tx.accountMessage)); // message を入力にする
	// SHA256_Final(digest, &sha_ctx); // digest に出力
    // ret = ECDSA_do_verify(digest, 32, tx.sig, tx.pubkey);
    //  if (ret == -1)
    //     {
    //     /* error */
    //     std::cout << "[ISFinalTX]Verify is error \n\n\n";
    //     }
    // else if (ret == 0)
    //     {
    //     /* incorrect signature */
    //     std::cout << "[ISFinalTX]incorrect signature \n\n\n";
    //     }
    // else   /* ret == 1 */
    //     {
    //     /* signature ok */
    //     std::cout << "[ISFinalTX]signature is OK\n\n\n";
    //     }
    // }


    /*
    // Basic checks that don't depend on any context
    if (tx.vin.empty())
        return state.Invalid(TxValidationResult::TX_CONSENSUS, "bad-txns-vin-empty");
    if (tx.vout.empty())
        return state.Invalid(TxValidationResult::TX_CONSENSUS, "bad-txns-vout-empty");
    // Size limits (this doesn't take the witness into account, as that hasn't been checked for malleability)
    if (::GetSerializeSize(tx, PROTOCOL_VERSION | SERIALIZE_TRANSACTION_NO_WITNESS) * WITNESS_SCALE_FACTOR > MAX_BLOCK_WEIGHT)
        return state.Invalid(TxValidationResult::TX_CONSENSUS, "bad-txns-oversize");
*/

    // Check for negative or overflow output values (see CVE-2010-5139)
    CAmount nValueOut = 0;
    for (const auto& txout : tx.vout)
    {
        if (txout.nValue < 0)
            return state.Invalid(TxValidationResult::TX_CONSENSUS, "bad-txns-vout-negative");
        if (txout.nValue > MAX_MONEY)
            return state.Invalid(TxValidationResult::TX_CONSENSUS, "bad-txns-vout-toolarge");
        nValueOut += txout.nValue;
        if (!MoneyRange(nValueOut))
            return state.Invalid(TxValidationResult::TX_CONSENSUS, "bad-txns-txouttotal-toolarge");
    }

    // Check for duplicate inputs (see CVE-2018-17144)
    // While Consensus::CheckTxInputs does check if all inputs of a tx are available, and UpdateCoins marks all inputs
    // of a tx as spent, it does not check if the tx has duplicate inputs.
    // Failure to run this check will result in either a crash or an inflation bug, depending on the implementation of
    // the underlying coins database.
    std::set<COutPoint> vInOutPoints;
    for (const auto& txin : tx.vin) {
        if (!vInOutPoints.insert(txin.prevout).second)
            return state.Invalid(TxValidationResult::TX_CONSENSUS, "bad-txns-inputs-duplicate");
    }

    if (tx.IsCoinBase())
    {
        if (tx.vin[0].scriptSig.size() < 2 || tx.vin[0].scriptSig.size() > 100)
            return state.Invalid(TxValidationResult::TX_CONSENSUS, "bad-cb-length");
    }
    else
    {
        for (const auto& txin : tx.vin)
            if (txin.prevout.IsNull())
                return state.Invalid(TxValidationResult::TX_CONSENSUS, "bad-txns-prevout-null");
    }

    return true;
}
