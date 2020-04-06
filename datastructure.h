#pragma once
#include <iostream>
using namespace std;

//structures

namespace datas
{
	template<typename item_typename>
	struct item // stack item
	{
		item<item_typename>* previous;
		item_typename var;
	};

	template<typename item_typename>
	struct list_item // list item
	{
		list_item<item_typename>* previous;
		item_typename var;
		list_item<item_typename>* next;
	};
}

//help variables

template<typename T>
datas::item<T>* previous_help; //stack item

template<typename T>
datas::item<T>* card; // stack item

template<typename T>
datas::list_item<T>* list_previous_help; //list item

template<typename T>
datas::list_item<T>* list_card; // list item

template<typename T>
datas::list_item<T>* list_next_help; //list item

//classes

template<class data_typename>
class data_struct
{
public:
	virtual data_typename current_item()=0; // return an current item
	virtual void push(data_typename variable)=0; // add an item to the data structure
	virtual data_typename pop()=0; // delete and return an current item
	virtual int size()=0; // return number of items of the data structure
};

template<class stack_typename>
class stack :public data_struct<stack_typename>
{
private:
	datas::item<stack_typename>* current;
	int stack_pointer;
public:
	stack() // constructor
	{
		current = nullptr;
		stack_pointer = 0;
	}
	virtual void push(stack_typename variable) // add an item to the stack
	{
		card<stack_typename> = new datas::item<stack_typename>;
		card<stack_typename>->var = variable;
		card<stack_typename>->previous = current;
		current = card<stack_typename>;
		stack_pointer++;
	}
	virtual stack_typename pop() // delete and return an top item
	{
		if (stack_pointer != 0)
		{
			stack_typename to_return;
			to_return = current->var;
			previous_help<stack_typename> = current->previous;
			delete current;
			current = previous_help<stack_typename>;
			stack_pointer--;
			return to_return;
		}
		else
		{
			throw 0;
		}
	}
	virtual stack_typename current_item() // return an current item, same as top but it's virtual function
	{
		return top();
	}
	virtual int size()                        // return number of items in the stack

	{
		return stack_pointer;
	}
	stack_typename top(); // return an top item
};


template<class list_typename>
class list :public data_struct<list_typename>
{
private:
	datas::list_item<list_typename>* current;
	int counter;
	int pointer;
public:
	list() // constructor
	{
		current = nullptr;
		counter = 0;
		pointer = 0;
	}
	virtual void push(list_typename variable) // add an item to the list
	{
		if (counter == 0)
		{
			list_card<list_typename> = new datas::list_item<list_typename>;
			list_card<list_typename>->previous = nullptr;
			list_card<list_typename>->next = nullptr;
			list_card<list_typename>->var = variable;
			current = list_card<list_typename>;
			counter++;
			pointer++;

		}
		else
		{
			list_next_help<list_typename> = current->next;
			list_previous_help<list_typename> = current;
			list_card<list_typename> = new datas::list_item<list_typename>;
			list_card<list_typename>->previous = current;
			list_card<list_typename>->next = current->next;
			list_card<list_typename>->var = variable;
			current = list_card<list_typename>;
			if (current->next != nullptr) list_next_help<list_typename>->previous = list_card<list_typename>;
			list_previous_help<list_typename>->next = current;
			counter++;
			pointer++;
		}
	}
	virtual list_typename pop() // delete and return an current item
	{
		if (counter != 0)
		{
			list_typename to_return = current->var;
			list_previous_help<list_typename> = current->previous;
			list_next_help<list_typename> = current->next;
			delete current;
			if (list_previous_help<list_typename> != nullptr) list_previous_help<list_typename>->next = list_next_help<list_typename>;
			if (list_next_help<list_typename> != nullptr) list_next_help<list_typename>->previous = list_previous_help<list_typename>;

			if (list_previous_help<list_typename> != nullptr) 
			{
				current = list_previous_help<list_typename>;
			}
			else if (list_next_help<list_typename> != nullptr) 
			{
				current = list_next_help<list_typename>;
			}
			else 
			{
				current = nullptr;
				pointer = 0;
			}

			counter--;
			return to_return;
		}
		else
		{
			throw 0;
		}
		
	}
	virtual list_typename current_item() // return current item
	{
		return current->var;
	}
	virtual int size()
	{
		return counter;
	}
	int current_position() // return current item position
	{
		return pointer;
	}
	void left() // if possible change current position one place to left
	{
		if (pointer != 1 && counter != 0)
		{
			current = current->previous;
			pointer--;
		}
	}
	void right() // if possible change current possition one place to right
	{
		if (pointer != counter && counter != 0)
		{
			current = current->next;
			pointer++;
		}
	}
};



// functions

template<typename T>
T stack<T>::top()
{
	return current->var;
}