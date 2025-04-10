#ifndef SEARCH_H
#define SEARCH_H
#include <fstream>
#include "unorderedLinkedList.h"

template <class t>
linkedListIterator<t> seqSearch(unorderedLinkedList<t> &list, const t &item)
{
    bool found = false;
    linkedListIterator<t> itRet;
    for (linkedListIterator<t> it = list.begin(); it != list.end() && !found; ++it)
    {
        if (*it == item)
        {
            found = true;
            itRet = it;
        }
    }
    if (found)
    {
        return itRet;
    }
    else
    {
        return list.end();
    }
}

template <class elemType>
int binarySearch(const elemType list[], int length, const elemType &item, int &comp, int first, int last)
{
    if (last < first)
        return -1;
    int mid = 0;
    mid = (first + last) / 2;
    comp++;
    if (list[mid] == item)
    {

        return mid;
    }
    else if (list[mid] > item)
    {
        return binarySearch(list, length, item, comp, first, mid - 1);
    }
    else if (list[mid] < item)
    {
        return binarySearch(list, length, item, comp, mid + 1, last);
    }
    return -1;
}

template <class t>
void bubbleSort(unorderedLinkedList<t> &list)
{
    std::ofstream out("bubble.txt");
    for (int iteration = 1; iteration < list.length(); iteration++)
    {
        out << "bsort" << iteration << std::endl;
        for (linkedListIterator<t> it = list.begin(); (it + 1) != list.end(); ++it)
        {
            if (*it > *(it + 1))
            {
                linkedListIterator<t> it1 = it + 1;
                swap(it, it1);
            }
        }
    }
}
template <class t>
void swap(linkedListIterator<t> &first, linkedListIterator<t> &second)
{
    t temp = *first;
    *first = *second;
    *second = temp;
}

#endif