#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <ctime>
#include <functional>
#include <openssl/sha.h>
class block
{
public:
    block(int, std::string, size_t = 0);
    std::string getData() { return data; };
    size_t getHash() { return currentHash; };
    bool validateHash();
    size_t getPrevHash() { return prevHash; };

private:
    std::string data;
    time_t nonce;
    size_t prevHash;
    size_t currentHash;
    int blockNum;
    void calculateHash();
};
#endif