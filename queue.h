#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

template<typename ItemType>
class queue
{
private:
    node<ItemType> *front, *rear;
    int count;
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
    
	void push (const ItemType& entery)
    {
        if (empty())
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
		while (front)
        {
            ptr = front;
            front = front->next;
            delete ptr;
        }
    }
};





#endif