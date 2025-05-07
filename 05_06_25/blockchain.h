#ifndef BLOCKC_H
#define BLOCKC_H

#include "block.h"
#include "linkedQueue.h"

class blockchain
{
public:
    blockchain();
    void insert(std::string);
    void verify();

private:
    linkedQueue<block> chain;
    int numBlocks;
};

#endif