#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"
#include <stdexcept>

template <class t>
class binarySearchTree : public binaryTree<t>
{
public:
    void insert(const t &insertItem);
    bool search(const t &searchItem);
    void deleteNode(const t &deleteItem);
    binarySearchTree(int (*comp)(const t &, const t &));

private:
    int (*compare)(const t &item1, const t &item2);
    void deleteFromTree(binaryNode<t> *&currentNode);
    bool search(const t &searchItem, binaryNode<t> *currentNode);
    void insert(binaryNode<t> *&insertItem, binaryNode<t> *&currentNode);
};
#endif