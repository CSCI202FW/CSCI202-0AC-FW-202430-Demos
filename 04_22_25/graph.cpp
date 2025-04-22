#include "graph.h"

graphType::graphType(int size = 0)
{
    if (size >= 0)
    {
        maxSize = size;
    }
    else
    {
        maxSize = 0;
    }
    if (maxSize > 0)
    {
        graph.resize(maxSize);
    }
}