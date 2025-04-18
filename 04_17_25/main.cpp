#include "binarySearchTree.h"
#include "AVLTree.h"
#include <iostream>
#include <random>

int compareNumbers(const int &first, const int &second);

int main()
{
    binarySearchTree<int> tree(compareNumbers);
    AVLTree<int> avltree(compareNumbers);
    std::uniform_int_distribution<int> distribution(5, 100);
    std::default_random_engine generator;
    int num = distribution(generator);

    for (int i = 0; i < num; i++)
    {

        try
        {

            tree.insert(distribution(generator));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << tree.inorderTraversal() << std::endl;
    std::cout << tree.preorderTraversal() << std::endl;
    std::cout << tree.postOrderTraversal() << std::endl;
    std::cout << "Generated num: " << num << std::endl;
    std::cout << "Tree Height: " << tree.treeheight() << std::endl;
    std::cout << "Tree Nodes: " << tree.treeNodeCount() << std::endl;
    std::cout << "Tree Leaves: " << tree.treeLeavesCount() << std::endl;

    return 0;
}

int compareNumbers(const int &first, const int &second)
{
    if (first < second)
        return -1;
    else if (first == second)
        return 0;
    else
        return 1;
}