#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

#include <vector>

using namespace std;

template<class container>
class my_iterator
{
	container c;
	int x;
public:
	my_iterator(const container &obj, int idx) { c = obj; x = idx; }
	my_iterator &operator++() { ++x; return *this; }
	my_iterator &operator--() { --x; return *this; }
	my_iterator operator*() const { return c.at[x]; }
	bool operator==(const container &other) const { return x == other.x; }
	bool operator!=(const container &other) const { return x != other.x; }

	//my_iterator(int idx) { x = idx; }

	~my_iterator() {}

private:

};


template<class IterType, class PredType>
IterType Find_If(IterType start, IterType end, PredType predicate)
{
	while (start != end)
	{
		if (predicate(*start))
			return start;
		++start;

	}
	return end;
}

int main()
{
	vector<int> x{ 3252,5213,61,523,121,35231,25213 }, y;
	my_iterator<vector<int>> itr(x,0);
	
}