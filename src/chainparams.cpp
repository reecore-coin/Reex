// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2020 The REEX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (     0, uint256("0x00000c1b8abb8755561c46ea298cf725c940ca71409f7024bc3ad82fdb1bdc7f"))
    (   500, uint256("0xa41b51720be8443abaf9445d1f80e8137d8834fd394dd9665ac107606d5428dc"))
    (  3500, uint256("0xdb2a3cbeb8a5d101893a2d2e6f19dc11bc96dd9e635267ef6b29909d46c15e43"))
    ( 15000, uint256("0x108dc0938f6285a53d074b9c2a803ade651102e8c9587970d014d7bf8d559944"))
    ( 28000, uint256("0x8d5cca7aceb236db91018887aa0df5f51ce4b06cc70ea656d8321bc804fda6cf"))
    ( 62000, uint256("0x03d938fb7b372b34ae710631b9e716d8f2687457938635f544d5b01b53954ae3"))
    ( 79000, uint256("0xe5d9136fe32f26ff0d6a23b31bcf84dfaa7a1ecd242e6cf224aaded3895e67bf"))
    ( 95000, uint256("0xb7bde5d0a8a224cf0766113774452c64f430fff7336f527ef3e3a4cb6057ae38"))
    (122000, uint256("0x6f07dd05a2281613c63121281bbaa68b7248a40a58c251af6924feeb8c8ca89d"))
    (125500, uint256("0xf9f6972155d5390189b9e938e9ceb973acaa3e528c7dd3aedc89840b7e1c76bc"))
    (175000, uint256("0x11b1869e51df821dfd2ce40f3b5c258fe6ef7a42886ebf90c8a5447a3c7c0e7e"))
    (185000, uint256("0x476410c9e8ea1b3938a4899ba8a83e926503d572e17e345419343532b7278de0"))
    (197000, uint256("0xecc5e92f2c66c60fcb4ccba13b99af9930276005d53104c8e48384566cda8454"))
    (200000, uint256("0xbfe173d299e7c659865951c3a3e438df3b646078d36834782fce248dfb2dee40"))
    (201000, uint256("0x9787f36200959eb2f15b6b5f7a566757ae9191525d3c9f16baf90369d96ea408"))
    (202000, uint256("0x2372a98da3e1f7cac2a098087aa554594534fcbb7cf97aab821e182aebf4f001"))
    (203000, uint256("0xabbb473cba421f2951ba96922309001ec5e0f75e51682c338a8ba17ebf86694b"))
    (204000, uint256("0xdb20c3e9e8f2417f4b74c409d1ea9876ecf1c9e94a015b6ef67f78d852dea74d"))
    (206000, uint256("0x133d00cc5e905cfd4e3e7691735c8bcf1c1aacbb8465c5251e5b4365dcf7814e"))
    (207000, uint256("0x15de72394dee00e442c6100891171e822a5acdd3a355569ad4abc3ffcffc22bc"))
    (208000, uint256("0xf739fa7ff4a505aca16b00d7095c91b159a5612de876ca5b45d1fa8d1964d799"))
    (209000, uint256("0x0b850a21439eccefaa950e830e61d7f6861c8635c23a85978e885f6397fcb012"))
    (210000, uint256("0x3d55d6355f83c4da60f0ec34abdb9fd8c1e91a2203a9424e92278e9e82b0a97c"))
    (213000, uint256("0x28dafd4873215b78b623e295930d9af6dfd16d938b136dc5937b1318ed59e933"))
    (220000, uint256("0xb4ae62468bf97ceff70927474ff764843a04af36a3e13611bf6e4f37a4360a73"))
    (226486, uint256("0x99f185edb63549e2947e905bc51852614307cb01453f5be56e645155b642231c"))
    (230000, uint256("0x15426fd9d7a125a72e418171fec833c5e9edbdfef970a492888227ca79e19376"))
    (240000, uint256("0xd81dde9a9c8a5bcb5c3e20570c9916ae18514fccc9ca0e079fc8760c0743ff97"))
    (250000, uint256("0xfd0b8a05097fa32c9570dcb1a26e6354c4bf50a3bc783177bea0fb2af7c7aa8b"))
    (260000, uint256("0x604fdc01c912161fec5a4b84b68c53d9cfb102893a24354d5796d963cacc1ec1"))
    (270000, uint256("0xe0356d2203bbe082ff45f17bde84ba2b0623aef2cffb19cd71b77bba4e12b6c1"))
    (274780, uint256("0x65f3d56aa289cd02ec1063639b8f7a8f5bc610b9b69fe28e925a67bfc90852d9"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1561286923, // * UNIX timestamp of last checkpoint block
    554438,     // * total number of transactions between genesis and last checkpoint(the tx=... number in the SetBestChain debug.log lines)
    1440        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0x01;
        pchMessageStart[1] = 0xf3;
        pchMessageStart[2] = 0x02;
        pchMessageStart[3] = 0xa4;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 43210;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 0;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 20 * 60;
        nTargetSpacing = 2 * 60;
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;
		nStakeInputMinimal = 20 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1;

        //  nTime: 1531169926
        //  nNonce: 474276
        //  Hash: 00000d6274a0459bc63c3b7ad6c03614bed636e2c43e10b466c553d03bb56ecc
        //  hashMerkleRoot: d356f4e8178a28f1ad5f15738db447731b86ca1a9a620ff8358fa607252f2220
        const char* pszTimestamp = "reecore mainnet nov2018";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04f4a8143f86ad8ac63791fbbdb8e0b91a8da88c8c693a95f6c2c13c063ea790f7960b8025a9047a7bc671d5cfe707a2dd2e13b86182e1064a0eea7bf863636363") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1542907235;
        genesis.nBits = 0x1e0ffff0;  // 00000ffff0000000000000000000000000000000000000000000000000000000
        genesis.nNonce = 347336;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000c1b8abb8755561c46ea298cf725c940ca71409f7024bc3ad82fdb1bdc7f"));
        assert(genesis.hashMerkleRoot == uint256("0x71db3668e0435a23f1222acfcc186b84699bc1f9da54dcbb3cff6bf04dbc04af"));

        vSeeds.push_back(CDNSSeedData("seeder.reecore.org", "seeder.reecore.org"));  

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 61);  // R
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 122); // r
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 189);     // +128
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        //BIP-44 reex is "222"
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xde).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "02dfbea67a4f4898feea5686dab729d1eb8a65119f39b739d2dbaf66067a8a9273";
        strMasternodePoolDummyAddress = "SsJVWUkt6HtSCY2SaJ2akeyJUg8bg1hW3S";
        nStartMasternodePayments = genesis.nTime + (3600); // one week after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee

        strTreasuryAddress = "RiG2XFS4UcrjnCtJYr6cZdFtdaJNi4ugcH"; // Empty Treasury Address = no Treasury
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0xec;
        pchMessageStart[2] = 0x52;
        pchMessageStart[3] = 0x1e;
        vAlertPubKey = ParseHex("04f4a8143f86ad8ac63791fbbdb8e0b91a8da88c8c693a95f6c2c13c063ea790f7960b8025a9047a7bc671d5cfe707a2dd2e13b8618");
        nDefaultPort = 15151;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // 
        nTargetSpacing = 2 * 60;  // 
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 21000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1525777781;
        genesis.nNonce = 21451168;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x06b942b8b7f0e05ea38e7871a0db70f71592cfb016ee0ae7d5988f9fea840201"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet addresses start with 's'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 48);
        // Testnet script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);
        // Testnet private keys start with 'k'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 108);
        // Testnet BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet bitcoin green BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04abb5e65280dda6a113fadfb9877f9c399532245fe1acb61de293ab298034d5084277fab3768774a3b68cbbe5021cc5049ec8c9997a13f64da1afa0bcfb156db1";
        strMasternodePoolDummyAddress = "SbJ4Qad4xc77PpLzMx6rUegAs6aUPWkcUq";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0xec;
        pchMessageStart[2] = 0x52;
        pchMessageStart[3] = 0x1e;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; //
        nTargetSpacing = 2 * 60;        // 
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1525777781;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 21451168;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 25151;
        //assert(hashGenesisBlock == uint256("0x06b942b8b7f0e05ea38e7871a0db70f71592cfb016ee0ae7d5988f9fea840201"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
