#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <ctime>
#include <functional>
#include <openssl/sha.h>
class block
{
public:
    // block(int, std::string, size_t = 0);
    block(int, std::string, const unsigned char *);
    std::string getData() { return data; };
    // size_t getHash() { return currentHash; };
    const unsigned char *getHash() const { return currentHash; };
    bool validateHash();
    // size_t getPrevHash() { return prevHash; };
    const unsigned char *getPrevHash() const { return prevHash; };

private:
    std::string data;
    time_t nonce;
    // size_t prevHash;
    // size_t currentHash;
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    unsigned char currentHash[SHA256_DIGEST_LENGTH];
    int blockNum;
    void calculateHash();
};
#endif