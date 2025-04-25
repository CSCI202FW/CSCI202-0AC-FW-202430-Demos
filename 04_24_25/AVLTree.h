#ifndef AVLTREE_H
#define AVLTREE_H
#include "binarySearchTree.h"
#include "linkedStack.h"
#include <sstream>

// lecture activity: test the delete code report any bugs found.
template <class t>
class AVLTree : public binarySearchTree<t>
{
public:
    void insert(const t &insertItem);
    AVLTree(int (*comp)(const t &, const t &));
    void deleteNode(const t &deleteItem);
    class Iterator
    {
    public:
        Iterator(binaryNode<t> *currentNode);
        bool hasNext();
        t next();
        Iterator operator++();
        t &operator*();

    private:
        linkedStack<binaryNode<t> *> nodeStack;
        void pushLeftNodes(binaryNode<t> *node); // used to do inorder traversal.
    };
    Iterator begin() { return Iterator(this->getRoot()); };
    Iterator find(const t &searchItem);
    Iterator end() { return Iterator(nullptr); };

private:
    void balanceFromLeft(nodeType<t> *&currentNode);
    void balanceFromRight(nodeType<t> *&currentNode);
    void rotateToLeft(nodeType<t> *&currentNode);
    void rotateToRight(nodeType<t> *&currentNode);
    void insertIntoAVL(nodeType<t> *&currentNode, nodeType<t> *newNode, bool &isTaller);
    void deleteNode(nodeType<t> *&currentNode, const t &deleteItem, bool &isShorter);
    void AVLTree<t>::deleteFromTree(nodeType<t> *&currentNode, bool &isShorter);
    void AVLTree<t>::replaceDelete(nodeType<t> *&currentNode, nodeType<t> *&deleteNode, nodeType<t> *&parent, bool &isShorter);
    Iterator find(const t &searchItem, binaryNode<t> *currentItem);
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
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;
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
        break;
    }
}

template <class t>
void AVLTree<t>::balanceFromRight(nodeType<t> *&currentNode)
{
    nodeType<t> *rChild = currentNode->rLink;
    switch (rChild->bfactor)
    {
    case -1:
        switch (rChild->lLink->bfactor)
        {
        case -1:
            currentNode->bfactor = 0;
            rChild->bfactor = 1;
            break;
        case 0:
            currentNode->bfactor = 0;
            rChild->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = -1;
            rChild->bfactor = 0;
        }
        rChild->lLink->bfactor = 0;
        rotateToRight(currentNode->rLink);
        rotateToLeft(currentNode);
        break;
    case 0:
        throw std::runtime_error("Right Subtree is balanced.");
    case 1:
        currentNode->bfactor = 0;
        rChild->bfactor = 0;
        rotateToLeft(currentNode);
        break;
    }
}

template <class t>
void AVLTree<t>::rotateToLeft(nodeType<t> *&currentNode)
{
    nodeType<t> *newRootNode;
    if (currentNode == nullptr || currentNode->rLink == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    newRootNode = currentNode->rLink;
    currentNode->rLink = newRootNode->lLink;
    newRootNode->lLink = currentNode;
    currentNode = newRootNode;
}

template <class t>
void AVLTree<t>::rotateToRight(nodeType<t> *&currentNode)
{
    nodeType<t> *newRootNode;
    if (currentNode == nullptr || currentNode->lLink == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    newRootNode = currentNode->lLink;
    currentNode->lLink = newRootNode->rLink;
    newRootNode->rLink = currentNode;
    currentNode = newRootNode;
}
template <class t>
void AVLTree<t>::deleteNode(const t &deleteItem)
{
    bool isShorter = false;
    delteNode(this->getRoot(), deleteItem, isShorter);
    /* nodeType<t> *current;
    nodeType<t> *currentParent;
    bool found = false;
    if (this->isEmpty())
    {
        throw std::invalid_argument("Cannot delete from an empty tree");
    }

    current = this->getRoot();
    currentParent = current;
    while (current != nullptr && !found)
    {
        int cmp = compare(deleteItem, *(*current));
        if (cmp == 0)
        {
            found = true;
        }
        else
        {
            currentParent = current;
            if (cmp == 1)
            {
                current = current->rLink;
            }
            else
            {
                current = current->lLink;
            }
        }
    }
    if (!found)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree");
    }
    else
    {
        if (current == this->getRoot())
        {
            deleteFromTree(this->getRoot());
        }
        else if (compare(deleteItem, *(*currentParent)) == -1)
        {
            deleteFromTree(currentParent->lLink);
        }
        else
        {
            deleteFromTree(currentParent->rLink);
        }
    } */
}

template <class t>
void AVLTree<t>::deleteFromTree(nodeType<t> *&currentNode, bool &isShorter)
{
    nodeType<t> *replace;
    nodeType<t> *replaceParent;
    nodeType<t> *temp;
    if (currentNode == nullptr)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree.");
    }
    if (currentNode->lLink == nullptr && currentNode->rLink == nullptr)
    {
        temp = currentNode;
        currentNode = nullptr;
        delete temp;
        isShorter = true;
    }
    else if (currentNode->lLink == nullptr)
    {
        temp = currentNode;
        currentNode = temp->rLink;
        delete temp;
        isShorter = true;
    }
    else if (currentNode->rLink == nullptr)
    {
        temp = currentNode;
        currentNode = temp->lLink;
        delete temp;
        isShorter = true;
    }
    else
    {
        replaceDelete(currentNode->lLink, currentNode, nullptr, isShorter);
        if (isShorter)
        {

            switch (currentNode->bfactor)
            {
            case -1:
                currentNode->bfactor = 0;
                isShorter = true;
                break;
            case 0:
                currentNode->bfactor = 1;
                isShorter = false;
                break;
            case 1:
                switch (currentNode->rLink)
                {
                case -1:
                    rotateToLeft(currentNode);
                    currentNode->bfactor = height(currentNode->rLink) - height(currentNode->lLink);
                    currentNode->rLink->bfactor = height(current->rLink->rLink) - height(current->rLink->lLink);
                    isShorter = true;
                    break;
                case 0:
                    rotateToLeft(currentNode);
                    currentNode->bfactor = height(currentNode->rLink) - height(currentNode->lLink);
                    currentNode->rLink->bfactor = height(current->rLink->rLink) - height(current->rLink->lLink);
                    isShorter = false;
                    break;
                case 1:
                    rotateToRight(currentNode->rLink);
                    rotateToLeft(currentNode);

                    currentNode->bfactor = height(currentNode->rLink) - height(currentNode->lLink);
                    currentNode->rLink->bfactor = height(current->rLink->rLink) - height(current->rLink->lLink);
                    isShorter = true;
                    break;
                }
            }
        }
    }
}

template <class t>
void AVLTree<t>::deleteNode(nodeType<t> *&currentNode, const t &deleteItem, bool &isShorter)
{

    if (currentNode == nullptr)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree");
    }
    int cmp = this->compare(deleteItem, **currentNode) if (cmp == 0)
    {
        deleteFromTree(currentNode, isShorter);
        // isShorter = true;
    }
    else if (cmp == -1)
    {
        deleteNode(currentNode->lLink, deleteItem, isShorter);
        if (isShorter)
        {
            switch (currentNode->bfactor)
            {
            case -1:
                currentNode->bfactor = 0;
                isShorter = true;
                break;
            case 0:
                currentNode->bfactor = 1;
                isShorter = false;
                break;
            case 1:
                rotateToRight(currentNode->rLink);
                rotateToLeft(currentNode);

                currentNode->bfactor = height(currentNode->rLink) - height(currentNode->lLink);
                currentNode->rLink->bfactor = height(current->rLink->rLink) - height(current->rLink->lLink);
                isShorter = true;
                break;
            }
        }
    }
    else
    {
        deleteNode(currentNode->rLink, deleteItem, isShorter);
        if (isShorter)
        {
            switch (currentNode->bfactor)
            {

            case -1:
                switch (currentNode->lLink->bfactor)
                {
                case -1:
                    rotateToRight(currentNode);
                    currentNode->bfactor = height(currentNode->rLink) - height(currentNode->lLink);
                    currentNode->lLink->bfactor = height(current->lLink->rLink) - height(current->lLink->lLink);
                    isShorter = true;
                    break;
                case 0:
                    rotateToRight(currentNode);
                    currentNode->bfactor = height(currentNode->rLink) - height(currentNode->lLink);
                    currentNode->lLink->bfactor = height(current->lLink->rLink) - height(current->lLink->lLink);
                    isShorter = false;
                    break;
                case 1:
                    rotateToLeft(currentNode->lLink);
                    rotateToRight(currentNode);
                    currentNode->bfactor = height(currentNode->rLink) - height(currentNode->lLink);
                    currentNode->lLink->bfactor = height(current->lLink->rLink) - height(current->lLink->lLink);
                    isShorter = true;
                    break;
                }
                isShorter = false;
                break;
            case 0:
                currentNode->bfactor = -1;
                isShorter = false;
                break;
            case 1:
                currentNode->bfactor = 0;
                isShorter = true;

                break;
            }
        }
    }
}

template <class t>
void AVLTree<t>::replaceDelete(nodeType<t> *&currentNode, nodeType<t> *&deleteNode, nodeType<t> *&parent, bool &isShorter)
{
    if (currentNode->rLink == nullptr)
    {
        t *tempData = deleteNode->data;
        deleteNode->data = currentNode->data;
        currentNode->data = tempData;
        if (currentNode == deleteNode->lLink)
        {
            deleteNode->lLink = currentNode->lLink;
        }
        else
        {
            parent->rLink = currentNode->lLink;
        }
        delete currentNode;
        currentNode = nullptr;
        isShorter = true;
    }
    else
    {
        replaceDelete(currentNode->rLink, currentNode, deleteNode, isShorter);
        if (isShorter)
        {
            switch (currentNode->bfactor)
            {
            case -1:
                switch (currentNode->lLink->bfactor)
                {
                case -1:
                    rotateToRight(currentNode);
                    currentNode->bfactor = height(currentNode->rLink) - height(currentNode->lLink);
                    currentNode->lLink->bfactor = height(current->lLink->rLink) - height(current->lLink->lLink);
                    isShorter = true;
                    break;
                case 0:
                    rotateToRight(currentNode);
                    currentNode->bfactor = height(currentNode->rLink) - height(currentNode->lLink);
                    currentNode->lLink->bfactor = height(current->lLink->rLink) - height(current->lLink->lLink);
                    isShorter = false;
                    break;
                case 1:
                    rotateToLeft(currentNode->lLink);
                    rotateToRight(currentNode);
                    currentNode->bfactor = height(currentNode->rLink) - height(currentNode->lLink);
                    currentNode->lLink->bfactor = height(current->lLink->rLink) - height(current->lLink->lLink);
                    isShorter = true;
                    break;
                }

                break;
            case 0:
                currentNode->bfactor = -1;
                isShorter = false;
                break;
            case 1:
                currentNode->bfactor = 0;
                isShorter = true;

                break;
            }
        }
    }
}
#endif