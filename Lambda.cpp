
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

int calculateMode(vector<int> &);
int rNum();

int main()
{
	int n;
	//Number of values to be read as input from user
	cout << "Enter the number of values to be read: " << endl; 
	cin >> n;


	vector<int> myVector(n);
	generate(myVector.begin(), myVector.end(), rNum);

	cout << endl << "Mode is: " << calculateMode(myVector) << endl;

	system("pause");

}

//Calculate mode
int calculateMode(vector<int>& vec) 
{
	return *max_element(vec.begin(), vec.end(), [&vec](int maxOccurElement, int nextElement)
	{
		cout << "First item is : " << maxOccurElement << " and second item is : " << nextElement << endl;
		return	count(vec.begin(), vec.end(), maxOccurElement)<count(vec.begin(), vec.end(), nextElement);
	});

}

int rNum()
{
	return (rand() % 12) + (rand() % 10);
}
