#ifndef AVLTREE_H
#define AVLTREE_H
#include "binarySearchTree.h"
#include <sstream>

template <class t>
class AVLTree : public binarySearchTree<t>
{
public:
    void insert(const t &insertItem);
    AVLTree(int (*comp)(const t &, const t &));
    void deleteNode(const t &deleteItem);

private:
    void balanceFromLeft(nodeType<t> *&currentNode);
    void balanceFromRight(nodeType<t> *&currentNode);
    void rotateToLeft(nodeType<t> *&currentNode);
    void rotateToRight(nodeType<t> *&currentNode);
    void insertIntoAVL(nodeType<t> *&currentNode, nodeType<t> *newNode, bool &isTaller);
};

template <class t>
AVLTree<t>::AVLTree(int (*comp)(const t &, const t &)) : binarySearchTree<t>(comp) {}

template <class t>
void AVLTree<t>::insert(const t &insertItem)
{
    bool isTaller = false;
    nodeType<t> *newNode = new nodeType<t>;
    newNode->data = new t(insertItem);
    newNode->bfactor = 0;
    newNode->left = nullptr;
    newNode->right = nullptr;
    insertIntoAVL(this->getRoot(), newNode, isTaller);
}

template <class t>
void AVLTree<t>::insertIntoAVL(nodeType<t> *&currentNode, nodeType<t> *newNode, bool &isTaller)
{
    if (currentNode == nullptr)
    {
        currentNode = newNode;
        isTaller = true;
    }
    else
    {
        int cmp = this->compare(**newNode, **currentNode);
        if (cmp == 0)
        {
            throw std::invalid_argument("No duplicates allowed");
        }
        else if (cmp == -1)
        {
            insertIntoAVL(currentNode->lLink, newNode, isTaller);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    balanceFromLeft(currentNode);
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = -1;
                    isTaller = true;
                    break;
                case 1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                }
            }
        }
        else
        {
            insertIntoAVL(currentNode->rLink, newNode, isTaller);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = 1;
                    isTaller = true;
                    break;
                case 1:
                    balanceFromRight(currentNode);
                    isTaller = false;
                }
            }
        }
    }
}

template <class t>
void AVLTree<t>::balanceFromLeft(nodeType<t> *&currentNode)
{
    nodeType<t> *lChild;
    nodeType<t> *lChild_RChild;
    lChild = currentNode->lLink;

    switch (lChild->bfactor)
    {
    case -1: // left subtree of the current node is left high
        currentNode->bfactor = 0;
        lChild->bfactor = 0;
        rotateToRight(currentNode);
        break;
    case 0: // left subtree of current node is balanced is an error
        throw std::runtime_error("Left subtree is balanced.");
    case 1: // left subtree of the current node is right high (current node is left high)
        lChild_RChild = lChild->rLink;
        switch (lChild_RChild->bfactor)
        {
        case -1:
            currentNode->bfactor = 1;
            lChild->bfactor = 0;
            break;
        case 0:
            currentNode->bfactor = 0;
            lChild->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = 0;
            lChild->bfactor = -1;
            break;
        }
        lChild_RChild->bfactor = 0;
        rotateToLeft(currentNode->lLink);
        rotateToRight(currentNode);
    }
}

#endif