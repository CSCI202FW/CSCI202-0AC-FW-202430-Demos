#ifndef NODE_H
#define NODE_H

template <class t>
struct node
{
    t *data;
    node<t> *link;
    ~node()
    {
        delete data;
    }
};

#endif