#pragma once
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "node.h"

template <typename ItemType>
class priority_queue
{
private:
	node<ItemType> *front, *rear;	// a pointer that points to the first element in the queue and another one to point to the last element
	int count;	// the size of the queue
public:
	priority_queue ()
	{
		front = rear = nullptr;
		count = 0;
	}

    priority_queue (priority_queue const &q)
    {
        front = rear = nullptr;
        count = 0;
        node<ItemType> * temp = q.front;
        while (temp){
            this->push(temp->data, temp->priority);
            temp = temp->next;
        }
    }


    bool empty ()
	{
		return count == 0;
	}

	int size ()
	{
		return count;
	}

	// inserting a new element in the queue based on a specific priority
	void push (const ItemType& entery, int priority)
	{
		if (empty())	// if empty make it the front if the queue
		{
			front = new node<ItemType>;
			front->data = entery;
			front->priority = priority;
			front->next	= nullptr;
			
			rear = front;
			count++;
		
			return;
		}
		
		node<ItemType> *ptr = new node<ItemType>;
		ptr->data = entery;
		ptr->priority = priority;
		ptr->next = nullptr;

		if (front->priority > ptr->priority)	// if it has more priority than the front, make it the front then.
		{
			ptr->next = front;
			front = ptr;
			count++;
			return;
		}

		node<ItemType> *temp = front;
		while (temp->next && (temp->next->priority) < ptr->priority)	// keep looping till you find the first element with less priority or end of queue
			temp = temp->next;

		ptr->next = temp->next;
		temp->next = ptr;
		count++;
	}

	// it removes the first element in the queue (the front)
	void pop ()
	{
		if (empty())
			return;

	    node<ItemType> *temp = front;
		front = front->next;
		
		delete temp;
        count--;
	}
	
	// returns the data of the first element in the queue
	ItemType Front ()
	{
		return front->data;
	}

	~priority_queue ()
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

