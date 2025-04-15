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
    int nodeCount(binaryNode<t> *p, int count = 0) const;
    int leavesCount(binaryNode<t> *p, int count = 0) const;
    int max(int x, int y) const;
};

#endif