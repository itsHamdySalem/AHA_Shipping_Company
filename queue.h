#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

template<typename ItemType>
class queue
{
private:
    node<ItemType> *front, *rear;	// a pointer that points to the first element in the queue and another one to point to the last element
    int count;	// the size of the queue
public:
	queue()
    {
        front = rear = nullptr;
        count = 0;
    }

    bool empty ()
    {
        return count == 0;
    }
    
	// inserting a new element in the queue at the back of the queue
	void push (const ItemType& entery)
    {
        if (empty())	// if empty make it the front if the queue
        {
            front = new node<ItemType>;
            front->data = entery;
            front->next = nullptr;

			rear = front;
            count++;
            
			return;
        }

        node<ItemType> *temp = new node<ItemType>;
        temp->data = entery;
        temp->next = nullptr;
        
		rear->next = temp;
        rear = temp;
        
		count++;
    }

    void pop ()
    {
        if (empty())
			return;

	    node<ItemType> *temp = front;
		front = front->next;
		
		delete temp;
        count--;
    }
    
	ItemType Front ()
    {
        return front->data;
    }
	
	int size ()
	{
		return count;
	}

	~queue ()
    {
        node<ItemType> *ptr;
		while (front)	// deleting queue
        {
            ptr = front;
            front = front->next;
            delete ptr;
        }
    }
};





#endif