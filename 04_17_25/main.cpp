#include "binarySearchTree.h"
#include "AVLTree.h"
#include "person.h"
#include <iostream>
#include <random>
#include <fstream>

int compareNumbers(const int &first, const int &second);
int compareByName(const Person &p1, const Person &p2);

// get the people from the array into the AVL tree.

// print the inorder traversal

int main()
{
    binarySearchTree<int> tree3(compareNumbers);
    AVLTree<int> tree(compareNumbers);
    std::uniform_int_distribution<int> distribution(5, 100);
    std::default_random_engine generator;
    int num = distribution(generator);
    AVLTree<int> tree2(compareNumbers);
    std::ofstream out("out.txt");

    for (int i = 0; i < num; i++)
    {

        try
        {

            tree3.insert(distribution(generator));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    tree.insert(45);
    tree.insert(26);
    tree.insert(75);

    tree.insert(25);
    tree.insert(87);
    tree.insert(46);
    tree.insert(94);
    tree.insert(58);
    tree.insert(56);
    std::cout << tree.inorderTraversal() << std::endl;
    std::cout << tree.preorderTraversal() << std::endl;
    std::cout << tree.postOrderTraversal() << std::endl;
    std::cout << "Generated num: " << num << std::endl;
    std::cout << "Tree Height: " << tree.treeheight() << std::endl;
    std::cout << "Tree Nodes: " << tree.treeNodeCount() << std::endl;
    std::cout << "Tree Leaves: " << tree.treeLeavesCount() << std::endl;
    out << tree.preorderTraversal() << std::endl;
    out.close();
    std::ifstream in("out.txt");
    while (!in.eof())
    {
        int x;
        in >> x;
        if (!in)
            break;
        tree2.insert(x);
    }
    std::cout << tree2.inorderTraversal() << std::endl;
    std::cout << tree2.preorderTraversal() << std::endl;
    std::cout << tree2.postOrderTraversal() << std::endl;

    Person **people = new Person *[10];
    people[0] = new Person("Brian Busch", 32, 168);
    people[1] = new Person("Amber Hammond", 49, 155);
    people[2] = new Person("Jason Buckles", 28, 182);
    people[3] = new Person("Richard Asbury", 42, 182);
    people[4] = new Person("Rebecca Rivera", 69, 174);
    people[5] = new Person("Nikia Shurtleff", 51, 163);
    people[6] = new Person("Derek Hancock", 29, 168);
    people[7] = new Person("Elias Gomez", 47, 184);
    people[8] = new Person("Timothy Michael", 49, 170);
    people[9] = new Person("Bernard McElroy", 60, 183);

    AVLTree<Person> peopleTree(compareByName);

    for (int i = 0; i < 10; i++)
    {
        delete people[i];
    }
    delete[] people;

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

int compareByName(const Person &p1, const Person &p2)
{
    if (p1.getName() > p2.getName())
    {
        return 1;
    }
    if (p1.getName() < p2.getName())
    {
        return -1;
    }
    if (p1.getName() == p2.getName())
    {
        return 0;
    }
    return 0;
}