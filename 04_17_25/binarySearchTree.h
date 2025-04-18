#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"
#include <stdexcept>

template <class t>
class binarySearchTree : public binaryTreeType<t>
{
public:
    void insert(const t &insertItem);
    bool search(const t &searchItem);
    void deleteNode(const t &deleteItem);
    binarySearchTree(int (*comp)(const t &, const t &));

protected:
    int (*compare)(const t &item1, const t &item2);

private:
    void deleteFromTree(nodeType<t> *&currentNode);
    bool search(const t &searchItem, nodeType<t> *currentNode);
    void insert(nodeType<t> *&insertItem, nodeType<t> *&currentNode);
};

template <class t>
binarySearchTree<t>::binarySearchTree(int (*comp)(const t &, const t &))
{
    this->compare = comp;
}

template <class t>
void binarySearchTree<t>::insert(const t &insertItem)
{
    nodeType<t> *newNode = new nodeType<t>;
    newNode->data = new t(insertItem);
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;
    insert(newNode, this->getRoot());
}
template <class t>
void binarySearchTree<t>::insert(nodeType<t> *&insertItem, nodeType<t> *&currentNode)
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
            insert(insertItem, currentNode->rLink);
        }
        else if (cmp == -1) // new node is smaller than current --> head left
        {
            insert(insertItem, currentNode->lLink);
        }
    }
}

template <class t>
bool binarySearchTree<t>::search(const t &searchItem)
{
    return search(searchItem, this->getRoot());
}

template <class t>
bool binarySearchTree<t>::search(const t &searchItem, nodeType<t> *currentNode)
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
        return search(searchItem, currentNode->rLink);
    }
    else if (cmp == -1)
    {
        return search(searchItem, currentNode->lLink);
    }
    return false;
}
template <class t>
void binarySearchTree<t>::deleteNode(const t &deleteItem)
{
    nodeType<t> *current;
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
    }
}

template <class t>
void binarySearchTree<t>::deleteFromTree(nodeType<t> *&currentNode)
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
    }
    else if (currentNode->lLink == nullptr)
    {
        temp = currentNode;
        currentNode = temp->rLink;
        delete temp;
    }
    else if (currentNode->rLink == nullptr)
    {
        temp = currentNode;
        currentNode = temp->lLink;
        delete temp;
    }
    else
    {
        replace = currentNode->lLink;
        replaceParent = nullptr;
        while (replace->rLink != nullptr)
        {
            replaceParent = replace;
            replace = replace->rLink;
        }
        t *tempData;
        tempData = currentNode->data;
        currentNode->data = replace->data;
        replace->data = tempData;
        if (replaceParent == nullptr)
        {
            currentNode->lLink = replace->lLink;
        }
        else
        {
            replaceParent->rLink = replace->lLink;
        }
        delete replace;
        replace = nullptr;
    }
}

#endif
