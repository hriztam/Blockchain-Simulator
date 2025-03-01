// Imports to make our lifes easier
// 1. iostream: Standard input/output stream
// 2. vector: Dynamic array
// 3. ctime: Date and time utilities
// 4. sstream: String stream
// 5. iomanip: Input/output manipulators
// 6. openssl/sha.h: SHA-256 hash function
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

// Function to calculate SHA-256 hash
string sha256(const string &data)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)data.c_str(), data.size(), hash);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << hex << setw(2) << setfill('0') << (int)hash[i];

    return ss.str();
}

// Block class to represent each block in the blockchain
class Block
{
public:
    int index;           // Block index
    time_t timestamp;    // Timestamp of block creation
    string transactions; // Transaction data
    string previousHash; // Hash of the previous block
    string hash;         // Current block hash
    int nonce;           // Nonce for proof-of-work

    // Constructor to initialize block
    Block(int idx, const string &tx, const string &prevHash)
        : index(idx), transactions(tx), previousHash(prevHash), nonce(0)
    {
        timestamp = time(nullptr);
        hash = calculateHash();
    }

    // Function to calculate the hash of the block
    string calculateHash() const
    {
        stringstream ss;
        ss << index << timestamp << transactions << previousHash << nonce;
        return sha256(ss.str());
    }
};

// Blockchain class to manage the chain of blocks
class Blockchain
{
private:
    vector<Block> chain; // Vector to store the chain of blocks
    int difficulty;      // Difficulty level for proof-of-work

public:
    Blockchain()
    {
        chain.push_back(createGenesisBlock());
        difficulty = 4; // Set difficulty (number of leading zeros)
    }

    // Create the genesis block
    Block createGenesisBlock()
    {
        return Block(0, "Genesis Block", "0");
    }

    // Get the latest block in the chain
    Block getLatestBlock() const
    {
        return chain.back();
    }

    // Add a new block to the chain
    void addBlock(const string &transactions)
    {
        Block newBlock(chain.size(), transactions, getLatestBlock().hash);
        proofOfWork(newBlock);
        chain.push_back(newBlock);
    }

    // Perform proof-of-work to mine a new block
    void proofOfWork(Block &block)
    {
        while (block.hash.substr(0, difficulty) != string(difficulty, '0'))
        {
            block.nonce++;
            block.hash = block.calculateHash();
        }
    }

    // Check if the blockchain is valid
    bool isChainValid() const
    {
        for (size_t i = 1; i < chain.size(); ++i)
        {
            const Block &currentBlock = chain[i];
            const Block &previousBlock = chain[i - 1];

            // Validate hash integrity and previous hash linkage
            if (currentBlock.hash != currentBlock.calculateHash() ||
                currentBlock.previousHash != previousBlock.hash)
                return false;
        }
        return true;
    }

    // Tamper with a block to simulate an attack
    void tamperBlock(int index, const string &newTransactions)
    {
        if (index < chain.size())
        {
            chain[index].transactions = newTransactions;
            chain[index].hash = chain[index].calculateHash();
        }
    }

    // Print the blockchain details
    void printChain() const
    {
        for (const auto &block : chain)
        {
            cout << "Index: " << block.index << endl;
            cout << "Timestamp: " << block.timestamp << endl;
            cout << "Transactions: " << block.transactions << endl;
            cout << "Previous Hash: " << block.previousHash << endl;
            cout << "Current Hash: " << block.hash << endl;
            cout << "Nonce: " << block.nonce << endl;
            cout << string(50, '-') << endl;
        }
    }
};

int main()
{
    Blockchain blockchain;

    // Add new blocks to the blockchain
    blockchain.addBlock("Transaction 1: A -> B");
    blockchain.addBlock("Transaction 2: C -> D");

    // Print initial blockchain state
    cout << "Initial Blockchain:\n";
    blockchain.printChain();
    cout << "Is blockchain valid? " << (blockchain.isChainValid() ? "Yes" : "No") << endl;

    // Simulate tampering with the blockchain
    blockchain.tamperBlock(1, "Tampered Transaction 1: X -> Y");

    // Print blockchain state after tampering
    cout << "\nBlockchain after tampering:\n";
    blockchain.printChain();
    cout << "Is blockchain valid? " << (blockchain.isChainValid() ? "Yes" : "No") << endl;

    return 0;
}
