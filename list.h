#include<iostream>
using namespace std;
#pragma once
#ifndef LIST_H
#define LIST_H

#include "node.h"

template <typename ItemType>
class list
{
private:
	node<ItemType> *head;	// head is pointer that points to the first node in the list
	int count;	// the count of nodes in the list ( size of the list)
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
		if (empty())	// if the list is empty 
		{
			head = new node<ItemType>;
			head->data = newEntry;
			head->next = nullptr;
			count++;
			return;
		}

        node <ItemType> *newNodePtr = new node<ItemType>;	// the new node holding newEntery
        newNodePtr->data = newEntry;
		newNodePtr->next = nullptr;

        node<ItemType> *temp1 = head;
		while (temp1->next)		// keep looping till you reach the tail of the list
			temp1 = temp1->next;		
		temp1->next = newNodePtr;	// make the tail points to new node 
        
		count++;	// increase the size of list
    }
     
	// get the data of the node at a specific index
	ItemType at (const int &idx)
	{
        //if (idx >= size())	return ;	// if the index is greater than the size of the list

		node<ItemType> *cur = head;
        
		for(int i = 0; i < idx; i++)	// keep looping till you reach the node with the given index
			cur = cur->next;
        
		return cur->data;	// return the data of that node
    }

	// it removes the first node with the given id
	void remove (const ItemType&  id)
	{
		if (empty())	// if empty there is nothing to be removed
			return;

		node<ItemType> *temp1 = head;

		if (head->data == id)	// if the head holds the data than make the head points to the next node and delete the head
		{
			head = head->next;
			delete temp1;
			count--;
			return;
		}

		while (temp1->next)	// keep looping till you find the data to be removed or the end of the list
		{
			if (temp1->next->data == id)	// if found remove it and make the pervious node points to the next of the removed node
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
		while (head)	// deleting the list
		{
			ptr = head;
			head = head->next;
			delete ptr;
		}
	}
	void Print ()
	{
		node<ItemType> *temp = head;
		while (temp)
		{
			cout << temp->data << ' ';
			temp = temp->next;
		}
		cout << '\n';
	}
};

#endif