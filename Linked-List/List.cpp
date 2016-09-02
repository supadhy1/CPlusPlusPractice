#include "List.h"
#include <iostream>
#include <memory>

using namespace std;

int main()
{
	//Initialize a new head node using function new_node
	shared_ptr<s_node<double>> headNode = shared_ptr<s_node<double>>(new s_node<double>);
	headNode->next = nullptr;
	headNode->prev = nullptr;
	headNode = new_node(1.1, headNode->next, headNode->prev);
	cout << "Head Node initialized with element: " << headNode->elem << endl;
	
	//To add a node at the start using function add_node
	shared_ptr<s_node<double>> newNode2 = shared_ptr<s_node<double>>(new s_node<double>);
	newNode2->next = nullptr;
	newNode2->prev = nullptr;
	newNode2 = new_node(2.2, newNode2->next, newNode2->prev);
	add_node(newNode2, headNode);
	cout << "Node added at the start with element: " << newNode2->elem << endl;

	shared_ptr<s_node<double>> newNode6 = shared_ptr<s_node<double>>(new s_node<double>);
	newNode6->next = nullptr;
	newNode6->prev = nullptr;
	newNode6 = new_node(6.6, newNode6->next, newNode6->prev);
	add_node(newNode6, headNode);
	cout << "Node added at the start with element: " << newNode6->elem << endl;
	
	//To add a node at the end using function append
	shared_ptr<s_node<double>> newNode3 = shared_ptr<s_node<double>>(new s_node<double>);
	newNode3->next = nullptr;
	newNode3->prev = nullptr;
	newNode3 = new_node(3.3, newNode3->next, newNode3->prev);
	append(newNode3, headNode);
	cout << "Node added at the end with element: " << newNode3->elem << endl;

	shared_ptr<s_node<double>> newNode7 = shared_ptr<s_node<double>>(new s_node<double>);
	newNode7->next = nullptr;
	newNode7->prev = nullptr;
	newNode7 = new_node(7.7, newNode7->next, newNode7->prev);
	append(newNode7, headNode);
	cout << "Node added at the end with element: " << newNode7->elem << endl;

	shared_ptr<s_node<double>> newNode8 = shared_ptr<s_node<double>>(new s_node<double>);
	newNode8->next = nullptr;
	newNode8->prev = nullptr;
	newNode8 = new_node(8.8, newNode8->next, newNode8->prev);
	append(newNode8, headNode);
	cout << "Node added at the end with element: " << newNode8->elem << endl;
	
	//To add an element with node at the start using function add_elem
	add_elem(9.9, headNode);
	cout << "New Node with element " << headNode->elem << " added at the start" << endl;

	add_elem(10.10, headNode);
	cout << "New Node with element " << headNode->elem << " added at the start" << endl;
	

	//To add node at nth location using function add_node_at
	shared_ptr<s_node<double>> newNode4 = shared_ptr<s_node<double>>(new s_node<double>);
	newNode4->next = nullptr;
	newNode4->prev = nullptr;
	newNode4 = new_node(4.4, newNode4->next, newNode4->prev);
	add_node_at(newNode4, headNode, 4);
	cout << "New node added at 4th location with element: " << newNode4->elem << endl;

	shared_ptr<s_node<double>> newNode5 = shared_ptr<s_node<double>>(new s_node<double>);
	newNode5->next = nullptr;
	newNode5->prev = nullptr;
	newNode5 = new_node(5.5, newNode5->next, newNode5->prev);
	add_node_at(newNode5, headNode, 7);
	cout << "New node added at 7th location with element: " << newNode5->elem << endl;

	shared_ptr<s_node<double>> newNode9 = shared_ptr<s_node<double>>(new s_node<double>);
	newNode9->next = nullptr;
	newNode9->prev = nullptr;
	newNode9 = new_node(11.11, newNode9->next, newNode9->prev);
	add_node_at(newNode9, headNode, 19); //testing for 'n' is too large 
	cout << "New node added at 19th location with element: " << newNode9->elem << endl;
	cout << "(Adding at the end of the list since 'n' is too large!)" << endl << endl;


	//To remove a node at the start of the list using function remove_node
	cout << "Size of the list before removal: " << count_s_node(headNode) << endl;
	cout << "Element removed from the start of the list: " << headNode->elem << endl;
	remove_node(headNode);
	cout << "Size of the list after removal: " << count_s_node(headNode) << endl << endl;

	//To remove the last node using function remove_last
	cout << "Size of the list before removal: " << count_s_node(headNode) << endl;
	int size_of_list = count_s_node(headNode);
	cout << "Element removed from end of the list: " << elem_at(headNode, size_of_list) << endl;
	remove_last(headNode);
	cout << "Size of the list after removal: " << count_s_node(headNode) << endl << endl;

	//To remove the last node using function remove_last
	cout << "Size of the list before removal: " << count_s_node(headNode) << endl;
	cout << "Node at 4th location removed from the list: " << elem_at(headNode, 4) << endl;
	remove_node_at(headNode, 4);
	cout << "Size of the list after removal: " << count_s_node(headNode) << endl << endl;

	cout << "Node at 2nd location removed from the list: " << elem_at(headNode, 2) << endl;
	remove_node_at(headNode, 2);
	cout << "Size of the list after removal: " << count_s_node(headNode) << endl;

	//To empty the list using function empty_list
	cout << "Size of the list before removal: " << count_s_node(headNode) << endl;
	empty_list(headNode);
	cout << "Size of the list after removal: " << count_s_node(headNode) << endl;

	cout << endl;
	cout << "Size of the list: " << count_s_node(headNode) << endl;

	system("pause");
}