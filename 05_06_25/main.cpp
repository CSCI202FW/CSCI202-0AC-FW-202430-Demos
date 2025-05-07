#include <iostream>

#include <string>
#include "blockchain.h"

int main()
{
    std::string message = "Space star ordering is based on the twin scientific principles of star-maths and wishy thinking.";
    std::string message2 = "Prepare to put mustard on those words, for you will soon be consuming them along with this slice of humble pie that comes direct from the oven of shame, set at gas mark 'egg on your face'.";
    std::string message3 = "prepare to put mustard on those words, for you will soon be consuming them along with this slice of humble pie that comes direct from the oven of shame, set at gas mark 'egg on your face'.";
    blockChain bc;
    bc.insert(message);
    bc.insert(message2);
    bc.insert(message3);
    bc.verify();
    return 0;
}