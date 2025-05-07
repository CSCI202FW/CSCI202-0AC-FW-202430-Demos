#ifndef BLOCKC_H
#define BLOCKC_H

#include "block.h"
#include "linkedQueue.h"

class blockChain
{
public:
    blockChain();
    void insert(std::string);
    void verify();

private:
    linkedQueue<block> chain;
    int numBlocks;
};

#endif