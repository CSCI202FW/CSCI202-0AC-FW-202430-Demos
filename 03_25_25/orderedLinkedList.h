#ifndef OLLIST_H
#define OLLIST_H

#include "linkedList.h"
#include <iostream>


//this was primarily taken from unorderedLinkedList from the class demo
//the compiler really wanted head->first, tail->last, data->info

template <class t>
class orderedLinkedList : public linkedList<t> {
public:
    void insert(const t &newInfo);
    void deleteNode(const t &deleteItem);
    bool search(const t &searchItem) const;
    void print(std::ostream &os) const;
    bool isEmptyList() const;
    int length() const;
};

template <class t>
void orderedLinkedList<t>::insert(const t &newInfo)
{
    node<t>* newNode = new node<t>;     //make a new node
    newNode->info = new t(newInfo);     //attach our new info
    newNode->link = nullptr;            //await to point to our next item

    if (this->isEmptyList()) {          //basic setup for a the first item in a list
        this->first = newNode;
        this->last = newNode;
    } else {                            //subsequent list items
        node<t>* current = this->first;
        node<t>* trail = nullptr; 

        while (current != nullptr && *(current->info) < newInfo) {
            trail = current;            //while current isn't at the end, the loop will look for info larger than newInfo
            current = current->link;
        }

        //once the conditions are met in the while loop one of three things will happen:

        if (trail == nullptr) {         //we add at the first location
            newNode->link = this->first;
            this->first = newNode;
        } 
        else {                          //we add somewhere in the middle
            newNode->link = current;
            trail->link = newNode;
        }

        if (current == nullptr) {       //we add at the very end
            this->last = newNode;
        }
    }
    this->count++;                      //increment the count to track how many items we have.
}

template <class t>
bool orderedLinkedList<t>::search(const t &searchItem) const
{
    node<t> *current;
    bool found = false;
    current = this->first;
    while (current != nullptr && !found)
    {
        if (*(current->info) == searchItem)
        {
            found = true;
        }
        else
        {
            current = current->link;
        }
    }
    return found;
}


template <class t>
void orderedLinkedList<t>::deleteNode(const t &deleteItem)
{
    node<t> *current;
    node<t> *trailCurrent;
    bool found;
    if (this->isEmptyList())
    {
        throw std::out_of_range("Cannot delete from empty list");
    }
    else
    {
        if (*(this->first->info) == deleteItem)
        {
            current = this->first;
            this->first = this->first->link;
            this->count--;
            if (this->first == nullptr)
            {
                this->last = nullptr;
            }
            delete current;
        }
        else
        {
            found = false;
            trailCurrent = this->first;
            current = this->first->link;
            while (current != nullptr && !found)
            {
                if (*(current->info) != deleteItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                {
                    found = true;
                }
            }
            if (found)
            {
                trailCurrent->link = current->link;
                this->count--;
                if (this->last == current)
                {
                    this->last = trailCurrent;
                }
                delete current;
            }
            else
            {
                throw std::out_of_range("Item not found in list. Cannot delete");
            }
        }
    }
}


//update pure virtual functions from linkedList
template <class t>
void orderedLinkedList<t>::print(std::ostream &os) const {
    node<t> *current = this->first;
    while (current != nullptr) {
        os << *(current->info) << std::endl;
        current = current->link;
    }
}

template <class t>
bool orderedLinkedList<t>::isEmptyList() const {
    return this->first == nullptr;
}

template <class t>
int orderedLinkedList<t>::length() const {
    return this->count;
}
#endif
