#ifndef BINARY_H
#define BINARY_H
#include <string>
#include <sstream>

template <class t>
struct binaryNode
{
    t *data;
    binaryNode<t> *left;
    binaryNode<t> *right;
    ~binaryNode() { delete data; };
    t &operator*()
    {
        return *data;
    };
};

template <class t>
class binaryTree
{
public:
    const binaryTree<t> &operator=(const binaryTree<t> &otherTree);
    binaryTree(const binaryTree<t> &otherTree);
    binaryTree();
    std::string inorderTraversal() const;
    std::string preorderTraversal() const;
    std::string postOrderTraversal() const;
    bool isEmpty() const;
    int treeheight() const;
    int treeNodeCount() const;
    int treeLeavesCount() const;
    ~binaryTree();
    virtual void insert(const t &insertItem) = 0;
    virtual bool search(const t &searchItem) = 0;
    virtual void deleteNode(const t &deleteItem) = 0;

protected:
    binaryNode<t> *&getRoot();

private:
    binaryNode<t> *root;
    void copyTree(binaryNode<t> *&copiedTreeRoot, binaryNode<t> *otherTreeRoot);
    void destroy(binaryNode<t> *&p);
    void inorder(binaryNode<t> *p, std::ostringstream &out) const;
    void preorder(binaryNode<t> *p, std::ostringstream &out) const;
    void postorder(binaryNode<t> *p, std::ostringstream &out) const;
    int height(binaryNode<t> *p) const;
    int nodeCount(binaryNode<t> *p) const;
    int leavesCount(binaryNode<t> *p) const;
    int max(int x, int y) const;
};
template <class t>
const binaryTree<t> &binaryTree<t>::operator=(const binaryTree<t> &otherTree)
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
binaryTree<t>::binaryTree(const binaryTree<t> &otherTree)
{
    this->root = nullptr;
    copyTree(this->root, otherTree.root);
}

template <class t>
void binaryTree<t>::copyTree(binaryNode<t> *&currentNode, binaryNode<t> *copyFromNode)
{
    if (copyFromNode == nullptr)
    {
        currentNode = nullptr;
    }
    else
    {
        currentNode = new binaryNode<t>;
        currentNode->data = new t(*copyFromNode->data);
        copyTree(currentNode->left, copyFromNode->left);
        copyTree(currentNode->right, copyFromNode->right);
    }
}

template <class t>
binaryTree<t>::binaryTree()
{
    root = nullptr;
}
template <class t>
void binaryTree<t>::destroy(binaryNode<t> *&currentNode)
{
    if (currentNode != nullptr)
    {
        destroy(currentNode->left);
        destroy(currentNode->right);
        delete currentNode;
        currentNode = nullptr;
    }
}

template <class t>
binaryTree<t>::~binaryTree()
{
    destroy(root);
}

template <class t>
bool binaryTree<t>::isEmpty() const
{
    return root == nullptr;
}

template <class t>
std::string binaryTree<t>::inorderTraversal() const
{
    std::ostringstream out;
    inorder(root, out);
    return out.str();
}

template <class t>
void binaryTree<t>::inorder(binaryNode<t> *currentNode, std::ostringstream &out) const
{
    if (currentNode == nullptr)
    {
        return;
    }
    inorder(currentNode->left, out);
    out << *(*currentNode) << std::endl; // dereference pointer to a node. dereference node to the data
    inorder(currentNode->right, out);
}

template <class t>
std::string binaryTree<t>::preorderTraversal() const
{
    std::ostringstream out;
    preorder(root, out);
    return out.str();
}
template <class t>
void binaryTree<t>::preorder(binaryNode<t> *currentNode, std::ostringstream &out) const
{
    if (currentNode == nullptr)
        return;
    // visit the node
    out << *(*currentNode) << std::endl;
    // visit the left tree
    preorder(currentNode->left, out);
    // visit the right tree
    preorder(currentNode->right, out);
}

template <class t>
std::string binaryTree<t>::postOrderTraversal() const
{
    std::ostringstream out;
    postorder(root, out);
    return out.str();
}

template <class t>
void binaryTree<t>::postorder(binaryNode<t> *currentNode, std::ostringstream &out) const
{
    if (currentNode == nullptr)
        return;
    // visit left
    postorder(currentNode->left, out);
    // visit right
    postorder(currentNode->right, out);
    // visit current
    out << currentNode->operator*() << std::endl;
}

template <class t>
int binaryTree<t>::treeheight() const
{
    return height(root);
}

template <class t>
int binaryTree<t>::height(binaryNode<t> *currentNode) const
{
    if (currentNode != nullptr)
    {
        return max(height(currentNode->left), height(currentNode->right)) + 1;
    }
    return 0;
}

template <class t>
int binaryTree<t>::max(int x, int y) const
{
    if (x >= y)
        return x;
    return y;
}

template <class t>
int binaryTree<t>::treeNodeCount() const
{
    return nodeCount(root);
}

template <class t>
int binaryTree<t>::nodeCount(binaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    return nodeCount(currentNode->left) + nodeCount(currentNode->right) + 1;
}

template <class t>
int binaryTree<t>::treeLeavesCount() const
{
    return leavesCount(root);
}

template <class t>
int binaryTree<t>::leavesCount(binaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    if (currentNode->left == nullptr && currentNode->right == nullptr)
    {
        return 1;
    }
    return leavesCount(currentNode->left) + leavesCount(currentNode->right);
}

template <class t>
binaryNode<t> *&binaryTree<t>::getRoot()
{
    return this->root;
}

#endif