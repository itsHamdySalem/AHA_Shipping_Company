#pragma once
#ifndef LIST_H
#define LIST_H

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
class list
{
private:
	node<ItemType> *head;
	int count;
public:
	list ()
	{
		head = nullptr;
		count = 0;
	}

	bool empty ()
	{
		return count == 0;
	}

	void add (const ItemType& newEntry)
    {
		if (empty())
		{
			head = new node<ItemType>;
			head->data = newEntry;
			head->next = nullptr;
			count++;
			return;
		}

        node <ItemType> *newNodePtr = new node<ItemType>;
        newNodePtr->data = newEntry;
		newNodePtr->next = nullptr;

        node<ItemType> *temp1 = head;
		while (temp1->next)
			temp1 = temp1->next;		
		temp1->next = newNodePtr;
        
		count++;
    }
     
	ItemType at (const int &idx)
	{
        if (idx >= size())	return nullptr;

		node<ItemType> *cur = head;
        
		for(int i = 0; i < idx; i++)
			cur = cur->next;
        
		return cur->data;
    }

	void remove (const ItemType&  id)
	{
		if (empty())
			return;

		node<ItemType> *temp1 = head;

		if (head->data == id)
		{
			head = head->next;
			delete temp1;
			return;
		}

		while (temp1->next)
		{
			if (temp1->next->data == id)
			{
				node<ItemType> *temp2 = temp1->next;
				temp1->next = temp1->next->next;

				delete temp2;
				count--;
				
				return;
			}
			
			temp1 = temp1->next;
		}
	}

	int size ()
	{
		return count;
	}

	~list ()
	{
		node<ItemType> *ptr;
		while (head)
		{
			ptr = head;
			head = head->next;
			delete ptr;
		}
	}
};
#endif