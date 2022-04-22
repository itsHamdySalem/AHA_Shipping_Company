#pragma once
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
using namespace std;

#ifndef NODE_H
#define NODE_H
template <typename ItemType>
struct node
{
	ItemType data;
	node *next;
};
#endif

template <typename ItemType>
class priority_queue
{
private:
	node<ItemType> *front, *rear;
	int count;
public:
	priority_queue ()
	{
		front = rear = nullptr;
		count = 0;
	}

	bool empty ()
	{
		count == 0;
	}

	int size ()
	{
		return count;
	}

	void push (const ItemType& entery, int priority)
	{
		if (empty())
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
		ptr->data = entery
		ptr->priority = priority;
		ptr->next = nullptr;

		if (front->priority < ptr->priority)
		{
			ptr->next = front;
			front = ptr;
			return;
		}

		node<ItemType> *temp = front;
		while (temp->next && temp->next->priority > ptr->priority)
			temp = temp->next;

		ptr->next = temp->next;
		temp->next = ptr;
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

	~priority_queue ()
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