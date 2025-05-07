#include "blockchain.h"

blockChain::blockChain()
{
    numBlocks = 0;
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    block genesis(numBlocks++, "Genesis Block", hash);
    chain.enqueue(genesis);
}

void blockChain::insert(std::string message)
{
    block newBlock(numBlocks++, message, chain.back().getHash());
    chain.enqueue(newBlock);
}

void blockChain::verify()
{
    linkedQueue<block> cpy(chain);
    const unsigned char *prevHash = nullptr;
    // int count = 0;
    while (!cpy.isEmptyQueue())
    {
        block current(cpy.dequeue());
        if (!current.validateHash())
        {
            throw std::runtime_error("Block has been changed");
        }
        const unsigned char *currentHash = current.getHash();
        if (prevHash != nullptr)
        {
            for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
            {
                if (prevHash[i] != currentHash[i])
                {
                    throw std::runtime_error("Chain has been changed");
                }
            }
        }
        prevHash = current.getHash();
    }
}
