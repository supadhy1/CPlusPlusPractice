#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Node {
private:
	string nodeName = "";
	vector <shared_ptr<Node>> childNodes;
	shared_ptr<Node> parentNode;
	int number_of_child = 0;

public:
	Node(string name, int childNumber) : nodeName(name), number_of_child(childNumber), parentNode(nullptr) {
	}

	~Node()
	{
		childNodes.clear();
	}

	shared_ptr<Node> getParentNode()
	{
		return parentNode;
	}

	void setParentNode(shared_ptr<Node> parent)
	{
		parentNode = parent;
	}
	string getNodeName() {
		return nodeName;
	}

	void setNodeName(string name) {
		name = nodeName;
	}

	vector<shared_ptr<Node>> getChildNodes() {
		return childNodes;

	}

	void setChildNodes(vector<shared_ptr<Node>> children) {
		childNodes = children;
	}

	int getNumber_Of_Child() {
		return number_of_child;
	}

	void setNumber_Of_Child(int number_of_children) {
		number_of_child = number_of_children;
	}

};

class Employee {
private:
	shared_ptr<Node> head;
public:
	Employee(shared_ptr<Node> elem)
	{
		setHead(elem);
	}

	shared_ptr<Node> getHead() {
		return head;
	}
	void setHead(shared_ptr<Node> elem) {
		head = elem;
	}
};

vector<shared_ptr<Node>> createChildNodes(shared_ptr<Node> parent)
{
	vector <shared_ptr<Node>> rVector;
	int count = 0;

	while (count < parent->getNumber_Of_Child()) {
		string employeeChild;
		int number_of_child_nodes;

		cout << "Enter the  employee name for employer: " << parent->getNodeName() << endl;
		cin >> employeeChild;
		cout << "How many employees report to " << employeeChild << " ? " << endl;
		cin >> number_of_child_nodes;
		shared_ptr<Node> newChildNode(new Node(employeeChild, number_of_child_nodes));
		newChildNode->setParentNode(parent);
		if (number_of_child_nodes > 0)
			newChildNode->setChildNodes(createChildNodes(newChildNode));
		rVector.push_back(newChildNode);
		count++;
	}
	return rVector;
}

void displayEmployeeWithNoNodes(shared_ptr<Node> currentNode) {
	vector<shared_ptr<Node>> childNodes = currentNode->getChildNodes();


	for (shared_ptr<Node> elem : childNodes)
	{
		if (elem->getNumber_Of_Child() > 0)
			displayEmployeeWithNoNodes(elem);
		else {
			std::cout << "child Node: " << elem->getNodeName() << "--> ";
			shared_ptr<Node> temp = elem;
			while (temp->getParentNode() != nullptr)
			{
				std::cout << "parent Node: " << temp->getParentNode()->getNodeName() << "--> ";
				temp = temp->getParentNode();
			}
			std::cout << endl;
		}
	}

}

int get3orMoreDescendants(shared_ptr<Node> currentNode) {
	int totalDescendants = currentNode->getNumber_Of_Child();

	vector<shared_ptr<Node>> childrenVec = currentNode->getChildNodes();
	for (shared_ptr<Node>child : childrenVec)
	{
		totalDescendants += get3orMoreDescendants(child);
	}
	if (totalDescendants >= 3) {
		cout << "Employee with 3 or more reportees: " << currentNode->getNodeName() << endl;

	}
	return totalDescendants;
}



int main()
{

	string empName;
	int no_of_children;
	cout << "Enter the employee name: " << endl;
	cin >> empName;
	cout << "How many employees report to you? " << endl;
	cin >> no_of_children;
	
	shared_ptr<Node> newNode(new Node(empName, no_of_children));
	Employee *empTree = new Employee(newNode);

	newNode->setChildNodes(createChildNodes(newNode));
	newNode->setParentNode(nullptr);
	cout << "Displaying all employees who do not have anyone reporting to them: " << endl;
	displayEmployeeWithNoNodes(empTree->getHead());
	cout << endl;

	cout << "Displaying all employees who have more than 3 employees reporting to them: " << endl;
	get3orMoreDescendants(newNode);

	system("pause");

}