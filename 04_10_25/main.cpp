#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <thread>

#include "unorderedLinkedList.h"
#include "searchSort.h"
// lecture activity Pick which sort you would rather implement in a program.

int main()
{
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