#pragma once

#include "node.h"


template <typename ItemType>
class stack
{
private:
	node<ItemType> *top;
    int count;
public:
    stack()
    {
		top = nullptr;
        count = 0;
    }

    bool empty ()
    {
        return count == 0;
    }

    void push (const ItemType& to_push)
    {
        node<ItemType> *temp = new node<ItemType>;
        temp->data = to_push;
        temp->next = top;
        
		top = temp;
        
		count++;
    }

    void pop ()
    {
        if (empty())
            return;

        node<ItemType> *temp = top;
        top = top->next;

		delete temp;
        count--;
    }

    ItemType top ()
    {
        return top->data;
    }
    
	int size ()
	{
		return count;
	}

	void print ()
    {
        node<ItemType> *ptr = top;
        if (ptr)
			while (ptr)
			{
				cout << '[' << ptr->data << "] -> ";
				printer = ptr->next;
			}
        cout << "NULL\n";
    }

	~stack ()
	{
		node<ItemType> *ptr;
		while (top)
		{
			ptr = top;
			top = top->next;
			delete ptr;
		}
	}

};




