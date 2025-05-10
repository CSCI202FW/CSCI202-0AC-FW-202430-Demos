#ifndef PQUEUE_H
#define PQUEUE_H

#include "linkedQueue.h"

template <class t>
class fakePriorityQueue : public linkedQueue<t>
{
public:
    void enqueue(const t &);
};

template <class t>
void fakePriorityQueue<t>::enqueue(const t &queueElement)
{
    node<t> *newNode;                        //new node
    newNode = new node<t>;
    newNode->data = new t(queueElement);
    newNode->link = nullptr;
    if (this->isEmptyQueue())                    //if empty, point to first spot
    {
        this->queueFront = newNode;
        this->queueRear = newNode;
    }
    else{
        node<t> *current = this->queueFront;        //if not empty, point to front and back
        node<t> *previous = nullptr;

        while (current != nullptr && queueElement <= *(current->data)){
            previous = current;                    //loop through the list by comparing data values
            current = current->link;
        }

        if (previous == nullptr){                    //insert at front if loop makes it back to nullptr
            newNode->link = this->queueFront;
            this->queueFront = newNode;
        }
        else{                                        //insert where *current stopped
            newNode->link = current;
            previous->link = newNode;
        }

        if (newNode->link == nullptr){                //update queueRear if added at the end
            this->queueRear = newNode;
        }
    }
}

#endif
