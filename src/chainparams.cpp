// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018 The STATERA developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "libzerocoin/Params.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6
{
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++)
    {
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
    (0, uint256("0x003f32d55d2f2912bb3c0d30123caad20e67614afa4fe91fcaa5d0173c9b60cd"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,1539449713,0,0
    //,
    //1533927507, // * UNIX timestamp of last checkpoint block
    //0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    //2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x003f32d55d2f2912bb3c0d30123caad20e67614afa4fe91fcaa5d0173c9b60cd"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,1539449713,0,0
    //,
    //1740710,
    //0,
    //250
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x003f32d55d2f2912bb3c0d30123caad20e67614afa4fe91fcaa5d0173c9b60cd"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,1539449713,0,0
    //,
    //1454124731,
    //0,
    //100
};

libzerocoin::ZerocoinParams *CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
    public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xd2;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x34;
        pchMessageStart[3] = 0x7b;
        vAlertPubKey = ParseHex("043826a918b48b7bc31df5dec12dea90893138af03faf454f705b84b69b8c9912614119efcb3647de84e0fec7cdeb56257fd55ca2b314c3fbbe9f443a86b825a80");
        nDefaultPort = 61555;
        bnProofOfWorkLimit = (~uint256(0) >> 10);
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 30; // STATERA: 30 seconds re check of block time
        nTargetSpacing = 1 * 30;  // STATERA: 30 seconds blocktime
	    //nMaturity = 9;
        nMaturity = 2;        
	    nMasternodeCountDrift = 20;
        nMaxMoneyOut = 90000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 45;

        //a.gonzalez - First rewarded block
        nFirstRewardBlock = nLastPOWBlock;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Jamal Khashoggi Trump to punish Saudis over journalist 13-10-2018";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 29000000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040e2ed3c781e36892573c2800dac148af2d54fb9d69fb5b0b2f83b8f90d398709108b4a7a7d36adaba532cd8f25db0bd1b5b53fc7598c6c6bc424b1d20fc42b5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1539449713;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 822705;

        hashGenesisBlock = genesis.GetHash();

    if(genesis.GetHash() != uint256("0x003f32d55d2f2912bb3c0d30123caad20e67614afa4fe91fcaa5d0173c9b60cd"))
        {
            printf("Searching for genesis block...\n");
            uint256 hashTarget; hashTarget.SetCompact(genesis.nBits);
            while(uint256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }

        assert(hashGenesisBlock == uint256("0x003f32d55d2f2912bb3c0d30123caad20e67614afa4fe91fcaa5d0173c9b60cd"));
        assert(genesis.hashMerkleRoot == uint256("0xee2c36ff79a02999aed3c1664baa9f9bad4c236de0f84569bca1fb07c141d2d5"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("base.ninja", "BASE-testnet.seed.base.ninja"));
        //vSeeds.push_back(CDNSSeedData("base.ninja", "BASE-testnet.seed2.base.ninja"));
        //vSeeds.push_back(CDNSSeedData("s3v3nh4cks.ddns.net", "s3v3nh4cks.ddns.net"));
        //vSeeds.push_back(CDNSSeedData("88.198.192.110", "88.198.192.110"));
        //Test Seeds at localhost
        vSeeds.push_back(CDNSSeedData("localhost", "localhost"));
        vSeeds.push_back(CDNSSeedData("192.168.1.4", "192.168.1.4"));
        vSeeds.push_back(CDNSSeedData("85.219.60.24", "85.219.60.24"));
        vSeeds.push_back(CDNSSeedData("stateradnsseed1.tk", "stateradnsseed1.tk"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        //fRequireRPCPassword = false;        // default true
        fMiningRequiresPeers = false;       // default true
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = true;     // default false
        fSkipProofOfWorkCheck = true;      // default false
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "043e6954a539df787aad90cc101fdc072a8f5d450cf95488d5d5078c14a8a2f85374458037fa6075dfa4bf07fa049de196088030cc4fa4e540f09d6ce52df483f8";
        strObfuscationPoolDummyAddress = "D8VUuZRW7Xi4upmrHueTd1nCNatvr5Fjsw";
        nStartMasternodePayments = genesis.nTime;

        /** Zerocoin */
        zerocoinModulus = "933034631025263371931683737195989150827432725945865978553405534489169230717565655238929262433328781519062047083173774855927756291088223912678240116686930017973091641521360882816116138803824875952592332072733008652132259870299952045041515826225603304440412903162411130235757590579023934850884265744437894881577";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100;       //full security level for accumulators
        nZerocoinHeaderVersion = 4;        //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zSTATERA to be stakable
    }

    const Checkpoints::CCheckpointData &Checkpoints() const
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
        pchMessageStart[0] = 0xd2;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("0467f38dcafdf2a1e3ae0e65a87da005123d25ba09ba515fb0df1e5293ee70e875709fb5d5dc093db426f022ff5adad04fae7d5e5fb4f4d310eb5571adcf34d90b");
        nDefaultPort = 61474;
        bnProofOfWorkLimit = (~uint256(0) >> 10);
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // STATERA: 30 seconds re check of block time
        nTargetSpacing = 1 * 60;  // STATERA: 30 seconds blocktime
        nMasternodeCountDrift = 4;
        nMaxMoneyOut = 90000000 * COIN;
        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 45;

        //a.gonzalez - First rewarded block
        nFirstRewardBlock = nLastPOWBlock;
        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1539449713;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 822705;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();

         hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("0x003f32d55d2f2912bb3c0d30123caad20e67614afa4fe91fcaa5d0173c9b60cd"))
        {
            printf("Searching for genesis block...\n");
            uint256 hashTarget; hashTarget.SetCompact(genesis.nBits);
            while(uint256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }

        assert(hashGenesisBlock == uint256("0x003f32d55d2f2912bb3c0d30123caad20e67614afa4fe91fcaa5d0173c9b60cd"));
        assert(genesis.hashMerkleRoot == uint256("0xee2c36ff79a02999aed3c1664baa9f9bad4c236de0f84569bca1fb07c141d2d5"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("base.ninja", "BASE-testnet.seed.base.ninja"));
        //vSeeds.push_back(CDNSSeedData("base.ninja", "BASE-testnet.seed2.base.ninja"));
        //vSeeds.push_back(CDNSSeedData("s3v3nh4cks.ddns.net", "s3v3nh4cks.ddns.net"));
        //vSeeds.push_back(CDNSSeedData("88.198.192.110", "88.198.192.110"));
         //Test Seeds at localhost
        vSeeds.push_back(CDNSSeedData("localhost", "localhost"));
        vSeeds.push_back(CDNSSeedData("192.168.1.4", "192.168.1.4"));
        vSeeds.push_back(CDNSSeedData("85.219.60.24", "85.219.60.24"));
        vSeeds.push_back(CDNSSeedData("statera1.dns-cloud.net", "statera1.dns-cloud.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet BASE addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet BASE script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet BASE BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char>>();
        // Testnet BASE BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char>>();
        // Testnet BASE BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char>>();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0427ea50ec1ea5b51ea63dfdbb59cd3c2f162a32e5f5cdd42589fa19fbb3c773a237fa5b6ccf3b6d7304219ae9b1dafbc4e14cc7e87ae19c21c726f9820fc0a8f9";
        //strSporkKeyOld = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";
        strObfuscationPoolDummyAddress = "04939f84ff23224f7d223207f8f94beccbe2302c0339f1effbd90b2c69fd5b47d3873abb1267f6f5927c04dd7a3446d927dee8d1a019dab4cf1ec3ea1425b985ef";
        nStartMasternodePayments = genesis.nTime; //Fri, 09 Jan 2015 21:05:58 GMT
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
        pchMessageStart[0] = 0xd2;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 60; // STATERA: 30 seconds re check of block time
        nTargetSpacing = 1 * 60;  // STATERA: 30 seconds blocktime
        bnProofOfWorkLimit = (~uint256(0) >> 10);
        genesis.nTime = 1539449713;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 822705;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();

        hashGenesisBlock = genesis.GetHash();
        if(genesis.GetHash() != uint256("0x003f32d55d2f2912bb3c0d30123caad20e67614afa4fe91fcaa5d0173c9b60cd"))
        {
            printf("Searching for genesis block...\n");
            uint256 hashTarget; hashTarget.SetCompact(genesis.nBits);
            while(uint256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                }
            }
            printf("block.nTime = %u \n", genesis.nTime);
            printf("block.nNonce = %u \n", genesis.nNonce);
            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }

        nDefaultPort = 61476;
        assert(hashGenesisBlock == uint256("0x003f32d55d2f2912bb3c0d30123caad20e67614afa4fe91fcaa5d0173c9b60cd"));
        assert(genesis.hashMerkleRoot == uint256("0xee2c36ff79a02999aed3c1664baa9f9bad4c236de0f84569bca1fb07c141d2d5"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

         //Test Seeds at localhost
        vSeeds.push_back(CDNSSeedData("localhost", "localhost"));
        vSeeds.push_back(CDNSSeedData("192.168.1.4", "192.168.1.4"));
        vSeeds.push_back(CDNSSeedData("85.219.60.24", "85.219.60.24"));
        vSeeds.push_back(CDNSSeedData("statera1.dns-cloud.net", "statera1.dns-cloud.net"));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData &Checkpoints() const
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
        nDefaultPort = 61478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData &Checkpoints() const
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


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams *)&unitTestParams;
}

const CChainParams &Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network)
    {
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
