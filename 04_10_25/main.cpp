#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <thread>

#include "unorderedLinkedList.h"
#include "searchSort.h"
#include "person.h"
// lecture activity Pick which sort you would rather implement in a program.

int compareByName(Person *&, Person *&);
int compareByAge(Person *&, Person *&);
int compareByHeight(Person *&, Person *&);

int main()
{

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

    quickSort(people, 0, 9, compareByAge);
    for (int i = 0; i < 10; i++)
    {
        people[i]->print();
    }
    std::cout << std::endl
              << std::endl;
    quickSort(people, 0, 9, compareByName);
    for (int i = 0; i < 10; i++)
    {
        people[i]->print();
    }
    std::cout << std::endl
              << std::endl;
    quickSort(people, 0, 9, compareByHeight);
    for (int i = 0; i < 10; i++)
    {
        people[i]->print();
    }
    std::cout << std::endl
              << std::endl;
    std::ifstream in("input.txt");
    unorderedLinkedList<int> list;
    unorderedLinkedList<int> slistB;
    unorderedLinkedList<int> slistS;
    unorderedLinkedList<int> slistM;
    int iList[1000000];
    int i = 0;
    while (!in.eof())
    {
        int x;
        in >> x;
        list.insert(x);
        iList[i] = x;
        i++;
    }
    slistB = list;
    slistS = list;
    slistM = list;

    int searchTerm = 9357854;
    linkedListIterator<int> it = seqSearch(list, searchTerm);

    // list.insertionSort();
    // mergeSort(iList, 0, 1000000);
    // std::cout << "Merge Sort Finished" << std::endl;
    /* for (int i = 0; i < 10000; i++)
    {
        std::cout << iList[i] << std::endl;
    } */

    std::thread bsortThread(bubbleSort<int>, std::ref(slistB));
    //  bubbleSort(list);
    std::thread sSortThread(selectionSort<int>, std::ref(slistS));
    // std::thread iSortThread(insertionSort<int>, std::ref(list), 1000000);
    slistM.mergeSort();
    std::cout << "Merge Sort Finished!" << std::endl;

    if (it == nullptr)
    {
        std::cout << "The item was not found in the list" << std::endl;
    }
    else
    {
        std::cout << *it << " is in the list." << std::endl;
    }
    // iSortThread.join();
    // std::cout<< "Insertion Sort Finished" << std::endl;
    sSortThread.join();
    std::cout << "Selection Sort Finished" << std::endl;
    bsortThread.join();
    std::cout << "bubble sort finished." << std::endl;

    return 0;
}

int compareByName(Person *&p1, Person *&p2)
{
    if (p1->getName() > p2->getName())
    {
        return 1;
    }
    if (p1->getName() < p2->getName())
    {
        return -1;
    }
    if (p1->getName() == p2->getName())
    {
        return 0;
    }
    return 0;
}
int compareByAge(Person *&p1, Person *&p2)
{
    if (p1->getAge() > p2->getAge())
    {
        return 1;
    }
    if (p1->getAge() < p2->getAge())
    {
        return -1;
    }
    if (p1->getAge() == p2->getAge())
    {
        return 0;
    }
    return 0;
}
int compareByHeight(Person *&p1, Person *&p2)
{
    if (p1->getHeight() > p2->getHeight())
    {
        return 1;
    }
    if (p1->getHeight() < p2->getHeight())
    {
        return -1;
    }
    if (p1->getHeight() == p2->getHeight())
    {
        return 0;
    }
    return 0;
}