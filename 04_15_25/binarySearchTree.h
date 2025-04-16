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

template <class t>
binarySearchTree<t>::binarySearchTree(int (*comp)(const t &item1, const t &item2))
{
    this->compare = comp;
}

template <class t>
void binarySearchTree<t>::insert(const t &insertItem)
{
    binaryNode<t> *newNode = new binaryNode<t>;
    newNode->data = new t(insertItem);
    newNode->left = nullptr;
    newNode->right = nullptr;
    insert(newNode, this->getRoot());
}
template <class t>
void binarySearchTree<t>::insert(binaryNode<t> *&insertItem, binaryNode<t> *&currentNode)
{
    if (currentNode == nullptr)
    {
        currentNode = insertItem;
    }
    else
    {
        int cmp = compare(*(*insertItem), *(*currentNode));
        if (cmp == 0)
        {
            throw std::invalid_argument("The item to be inserted is already in the tree -- duplicates are not allowed");
        }
        else if (cmp == 1) // new node is larger than current --> head right
        {
            insert(insertItem, currentNode->right);
        }
        else if (cmp == -1) // new node is smaller than current --> head left
        {
            insert(insertItem, currentNode->left);
        }
    }
}

template <class t>
bool binarySearchTree<t>::search(const t &searchItem)
{
    return search(searchItem, this->getRoot());
}

template <class t>
bool binarySearchTree<t>::search(const t &searchItem, binaryNode<t> *currentNode)
{
    if (currentNode == nullptr)
    {
        return false;
    }
    int cmp = compare(searchItem, *(*currentNode));
    if (cmp == 0)
    {
        return true;
    }
    if (cmp == 1)
    {
        return search(searchItem, currentNode->right);
    }
    else if (cmp == -1)
    {
        return search(searchItem, currentNode->left);
    }
    return false;
}
template <class t>
void binarySearchTree<t>::deleteNode(const t &deleteItem)
{
    binaryNode<t> *current;
    binaryNode<t> *currentParent;
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
                current = current->right;
            }
            else
            {
                current = current->left;
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
            deleteFromTree(currentParent->left);
        }
        else
        {
            deleteFromTree(currentParent->right);
        }
    }
}

template <class t>
void binarySearchTree<t>::deleteFromTree(binaryNode<t> *&currentNode)
{
    binaryNode<t> *replace;
    binaryNode<t> *replaceParent;
    binaryNode<t> *temp;
    if (currentNode == nullptr)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree.");
    }
    if (currentNode->left == nullptr && currentNode->right == nullptr)
    {
        temp = currentNode;
        currentNode = nullptr;
        delete temp;
    }
    else if (currentNode->left == nullptr)
    {
        temp = currentNode;
        currentNode = temp->right;
        delete temp;
    }
    else if (currentNode->right == nullptr)
    {
        temp = currentNode;
        currentNode = temp->left;
        delete temp;
    }
    else
    {
        replace = currentNode->left;
        replaceParent = nullptr;
        while (replace->right != nullptr)
        {
            replaceParent = replace;
            replace = replace->right;
        }
        t *tempData;
        tempData = currentNode->data;
        currentNode->data = replace->data;
        replace->data = tempData;
        if (replaceParent == nullptr)
        {
            currentNode->left = replace->left;
        }
        else
        {
            replaceParent->right = replace->left;
        }
        delete replace;
        replace = nullptr;
    }
}

#endif