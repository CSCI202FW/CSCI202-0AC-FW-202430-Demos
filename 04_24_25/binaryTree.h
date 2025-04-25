#ifndef BINARY_H
#define BINARY_H
#include <string>
#include <sstream>

template <class t>
struct nodeType
{
    t *data;
    nodeType<t> *lLink;
    nodeType<t> *rLink;
    ~nodeType() { delete data; };
    int bfactor;
    t &operator*()
    {
        return *data;
    };
};

template <class t>
class binaryTreeType
{
public:
    const binaryTreeType<t> &operator=(const binaryTreeType<t> &otherTree);
    binaryTreeType(const binaryTreeType<t> &otherTree);
    binaryTreeType();
    std::string inorderTraversal() const;
    std::string preorderTraversal() const;
    std::string postOrderTraversal() const;
    bool isEmpty() const;
    int treeheight() const;
    int treeNodeCount() const;
    int treeLeavesCount() const;
    ~binaryTreeType();
    virtual void insert(const t &insertItem) = 0;
    virtual bool search(const t &searchItem) = 0;
    virtual void deleteNode(const t &deleteItem) = 0;

protected:
    nodeType<t> *&getRoot();

private:
    nodeType<t> *root;
    void copyTree(nodeType<t> *&copiedTreeRoot, nodeType<t> *otherTreeRoot);
    void destroy(nodeType<t> *&p);
    void inorder(nodeType<t> *p, std::ostringstream &out) const;
    void preorder(nodeType<t> *p, std::ostringstream &out) const;
    void postorder(nodeType<t> *p, std::ostringstream &out) const;
    int height(nodeType<t> *p) const;
    int nodeCount(nodeType<t> *p) const;
    int leavesCount(nodeType<t> *p) const;
    int max(int x, int y) const;
};
template <class t>
const binaryTreeType<t> &binaryTreeType<t>::operator=(const binaryTreeType<t> &otherTree)
{
    if (this != &otherTree)
    {
        if (root != nullptr)
        {
            destroy(root);
        }
        if (otherTree.root == nullptr)
        {
            root = nullptr;
        }
        else
        {
            copyTree(root, otherTree.root);
        }
    }
}
template <class t>
binaryTreeType<t>::binaryTreeType(const binaryTreeType<t> &otherTree)
{
    this->root = nullptr;
    copyTree(this->root, otherTree.root);
}

template <class t>
void binaryTreeType<t>::copyTree(nodeType<t> *&currentNode, nodeType<t> *copyFromNode)
{
    if (copyFromNode == nullptr)
    {
        currentNode = nullptr;
    }
    else
    {
        currentNode = new nodeType<t>;
        currentNode->data = new t(*copyFromNode->data);
        copyTree(currentNode->lLink, copyFromNode->lLink);
        copyTree(currentNode->rLink, copyFromNode->rLink);
    }
}

template <class t>
binaryTreeType<t>::binaryTreeType()
{
    root = nullptr;
}
template <class t>
void binaryTreeType<t>::destroy(nodeType<t> *&currentNode)
{
    if (currentNode != nullptr)
    {
        destroy(currentNode->lLink);
        destroy(currentNode->rLink);
        delete currentNode;
        currentNode = nullptr;
    }
}

template <class t>
binaryTreeType<t>::~binaryTreeType()
{
    destroy(root);
}

template <class t>
bool binaryTreeType<t>::isEmpty() const
{
    return root == nullptr;
}

template <class t>
std::string binaryTreeType<t>::inorderTraversal() const
{
    std::ostringstream out;
    inorder(root, out);
    return out.str();
}

template <class t>
void binaryTreeType<t>::inorder(nodeType<t> *currentNode, std::ostringstream &out) const
{
    if (currentNode == nullptr)
    {
        return;
    }
    inorder(currentNode->lLink, out);
    out << *(*currentNode) << std::endl; // dereference pointer to a node. dereference node to the data
    inorder(currentNode->rLink, out);
}

template <class t>
std::string binaryTreeType<t>::preorderTraversal() const
{
    std::ostringstream out;
    preorder(root, out);
    return out.str();
}
template <class t>
void binaryTreeType<t>::preorder(nodeType<t> *currentNode, std::ostringstream &out) const
{
    if (currentNode == nullptr)
        return;
    // visit the node
    out << *(*currentNode) << std::endl;
    // visit the left tree
    preorder(currentNode->lLink, out);
    // visit the right tree
    preorder(currentNode->rLink, out);
}

template <class t>
std::string binaryTreeType<t>::postOrderTraversal() const
{
    std::ostringstream out;
    postorder(root, out);
    return out.str();
}

template <class t>
void binaryTreeType<t>::postorder(nodeType<t> *currentNode, std::ostringstream &out) const
{
    if (currentNode == nullptr)
        return;
    // visit left
    postorder(currentNode->lLink, out);
    // visit right
    postorder(currentNode->rLink, out);
    // visit current
    out << currentNode->operator*() << std::endl;
}

template <class t>
int binaryTreeType<t>::treeheight() const
{
    return height(root);
}

template <class t>
int binaryTreeType<t>::height(nodeType<t> *currentNode) const
{
    if (currentNode != nullptr)
    {
        return max(height(currentNode->lLink), height(currentNode->rLink)) + 1;
    }
    return 0;
}

template <class t>
int binaryTreeType<t>::max(int x, int y) const
{
    if (x >= y)
        return x;
    return y;
}

template <class t>
int binaryTreeType<t>::treeNodeCount() const
{
    return nodeCount(root);
}

template <class t>
int binaryTreeType<t>::nodeCount(nodeType<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    return nodeCount(currentNode->lLink) + nodeCount(currentNode->rLink) + 1;
}

template <class t>
int binaryTreeType<t>::treeLeavesCount() const
{
    return leavesCount(root);
}

template <class t>
int binaryTreeType<t>::leavesCount(nodeType<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    if (currentNode->lLink == nullptr && currentNode->rLink == nullptr)
    {
        return 1;
    }
    return leavesCount(currentNode->lLink) + leavesCount(currentNode->rLink);
}

template <class t>
nodeType<t> *&binaryTreeType<t>::getRoot()
{
    return this->root;
}

#endif