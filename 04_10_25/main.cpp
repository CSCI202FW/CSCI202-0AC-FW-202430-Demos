#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <thread>

#include "unorderedLinkedList.h"
#include "searchSort.h"

int main()
{
    std::ifstream in("input.txt");
    unorderedLinkedList<int> list;
    int i = 0;
    while (i < 100000)
    {
        int x;
        in >> x;
        list.insert(x);
        i++;
    }

    int searchTerm = 9357854;
    linkedListIterator<int> it = seqSearch(list, searchTerm);
    if (it == nullptr)
    {
        std::cout << "The item was not found in the list" << std::endl;
    }
    else
    {
        std::cout << *it << " is in the list." << std::endl;
    }
    bubbleSort(list);
    std::cout << "bubble sort finished." << std::endl;

    return 0;
}