#include "block.h"

/* block::block(int blockNum, std::string data, size_t prevHash) : blockNum(blockNum), prevHash(prevHash), data(data)
{
    this->nonce = time(NULL);
    calculateHash();
} */

block::block(int blockNum, std::string data, const unsigned char *prevHash) : blockNum(blockNum), data(data)
{
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        this->prevHash[i] = prevHash[i];
    }
    this->nonce = time(NULL);
    calculateHash();
}

bool block::validateHash()
{
    // std::hash<std::string> str_hash;
    // std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + std::to_string(prevHash);
    // size_t newHash = str_hash(hashString);
    unsigned char newHash[SHA256_DIGEST_LENGTH];
    std::string phash(prevHash, prevHash + sizeof(prevHash) / sizeof(prevHash[0]));
    std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + phash;
    SHA256((unsigned char *)hashString.c_str(), hashString.length(), newHash);
    bool same = true;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        if (currentHash[i] != newHash[i])
        {
            same = false;
        }
    }
    return same;
}

void block::calculateHash()
{
    // std::hash<std::string> str_hash;
    // std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + std::to_string(prevHash);
    // currentHash = str_hash(hashString);

    std::string phash(prevHash, prevHash + sizeof(prevHash) / sizeof(prevHash[0]));
    std::string hashString = std::to_string(blockNum) + std::to_string(nonce) + data + phash;
    SHA256((unsigned char *)hashString.c_str(), hashString.length(), currentHash);
}