#ifndef _MYLIST_H_
#define _MYLIST_H_

#include <memory>

using namespace std;

template <class T>
struct s_node {
	T elem;
	shared_ptr<s_node<T>> next;
	shared_ptr<s_node<T>> prev;
};

/*
Allocates and returns a new node with the given pointers. You may create nodes with nullptrs.
*/
template <class T>
shared_ptr<s_node<T>> new_node(T elem, shared_ptr<s_node<T>> next, shared_ptr<s_node<T>> previous)
{
	shared_ptr<s_node<T>> newNode = shared_ptr<s_node<T>>(new s_node<T>);
	newNode->elem = elem;
	newNode->next = next;
	newNode->prev = previous;
	return newNode;
}

/*
Inserts a node at the start of the list. DO NOT add a nullptr pointer.
Do not iterate the list.
*/
template <class T>
void add_node(shared_ptr<s_node<T>> node, shared_ptr<s_node<T>> &head)
{
	if (head == nullptr)//if its an empty list
	{
		node->next = nullptr;
		node->prev = nullptr;
		head = node;
	}
	else
	{
		node->prev = nullptr;
		node->next = head;
		head->prev = node;
		head = node;
	}
}

/*
Creates a new node with elem and adds it to head.
Do not iterate the list.
*/
template <class T>
void add_elem(T elem, shared_ptr<s_node<T>> &head)
{
	shared_ptr<s_node<T>> newNode = shared_ptr<s_node<T>>(new s_node<T>);

	newNode->elem = elem;

	newNode->prev = nullptr;
	newNode->next = head;
	if (head != nullptr)
	{
		head->prev = newNode;
		head = newNode;
	}
}

/*
Adds a node to the end of a list. DO NOT add a nullptr pointer.
Iterate at most one time.
*/
template <class T>
void append(shared_ptr<s_node<T>> node, shared_ptr<s_node<T>> &head)
{
	shared_ptr<s_node<T>> temp = head;
	while (temp->next != nullptr)
		temp = temp->next;
	temp->next = node;
	node->prev = temp;
	node->next = nullptr;
}

/*
Adds a node at index n of a list or at the end of the list if n is too large.
Iterate at most one time.
*/
template <class T>
void add_node_at(shared_ptr<s_node<T>> node, shared_ptr<s_node<T>> &head, int n)
{
	shared_ptr<s_node<T>> temp = head;
	int count = count_s_node(head);
	if (count >= n)
	{
		int i = 1;
		cout << "Head Node: " << head->elem << endl;

		while (i < n - 1)
		{
			temp = temp->next;
			i++;
		}
		node->prev = temp;
		node->next = temp->next;
		node->next->prev = node;
		temp->next = node;

	}
	else   //If n is too large just append the node
		append(node, head);
}

/*
Removes the first node from the list. Returns elem and frees the node from memory.
Do not iterate the list.
*/
template <class T>
T remove_node(shared_ptr<s_node<T>> &head)
{
	if (head == nullptr) // if its an empty list
	{
		T val = head->elem;
		return val;
	}

	else if (head->next == nullptr)
	{
		T val = head->elem;
		head = nullptr;
		return val;
	}

	else
	{
		T val = head->elem;
		head = head->next;
		head->prev = nullptr;
		return val;
	}
}

/*
Removes the last node from the list.
Iterate at most one time.
*/
template <class T>
T remove_last(shared_ptr<s_node<T>> &head)
{

	if (head == nullptr) // if its an empty list
		return NULL;
	else
	{
		shared_ptr<s_node<T>> temp = head;
		while (temp->next != nullptr)
			temp = temp->next;
		T val = temp->elem;
		temp->prev->next = nullptr;
		return val;
	}
}

/*
Removes the node at index n or the last node.
Iterate at most one time.
*/
template <class T>
T remove_node_at(shared_ptr<s_node<T>> &head, int n)
{
	int count = 0;
	if (head == nullptr) // if its an empty list
		return NULL;
	else
	{
		shared_ptr<s_node<T>> temp = head;
		while (temp->next != nullptr && count < n - 1)
		{
			temp = temp->next;
			count++;
		}

		T val = temp->elem;
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		return val;
	}
}

/*
Returns the value the length of the list.
Iterate at most one time.
*/
template <class T>
int count_s_node(shared_ptr<s_node<T>> head)
{

	int count = 0;
	if (head != nullptr)
	{
		shared_ptr<s_node<T>> temp = head;
		while (temp != nullptr)
		{
			temp = temp->next;
			count++;
		}
	}
	return count;
}

/*
Frees all the nodes in the list.
CHALLENGE: Write in two lines for +5 extra credit (allowed to use other methods written in this assignment)
*/
template <class T>
void empty_list(shared_ptr<s_node<T>> &head)
{
	while (head != nullptr)
		remove_node(head);
}

/*
Returns a pointer to the node at index n or the last node.
Iterate at most one time.
*/
template <class T>
shared_ptr<s_node<T>> node_at(shared_ptr<s_node<T>> head, int n)
{
	int count = 0;
	if (head == nullptr) // if its an empty list
		return nullptr;
	else
	{
		shared_ptr<s_node<T>> temp = head;
		while (temp->next != nullptr && count < n)
		{
			temp = temp->next;
			count++;
		}
		return temp;
	}
}

/*
Returns the elem at index n or the last node.
Iterate at most one time.
*/
template <class T>
T elem_at(shared_ptr<s_node<T>> head, int n)
{

	int count = 0;
	if (head == nullptr)// if its an empty list
	{
		//cout << "List is empty!" << endl;
		return NULL;
	}
	else
	{
		shared_ptr<s_node<T>> temp = head;
		while (temp->next != nullptr && count < n - 1)
		{
			temp = temp->next;
			count++;
		}
		T val = temp->elem;
		return val;
	}
}

#endif
