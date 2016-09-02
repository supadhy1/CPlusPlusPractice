#include <iostream>
#include <algorithm>
#include "MyString.h"

using namespace std;

// Default constructor for Pascal String
String::String() {
	arr = new char[1];
	arr[0] = 0;
	len = 0;
}

// Constructor. Converts a C-string to a String object.  Original
String::String(const char *s) {
	len = strlen(s);
	arr = new char[len + 1];
	std::copy(s, s + len + 1, arr);

}

char intToChar(int var)
{
	char c;
	if (var > 0 && var <= 9)
		c = '0' + var;
	else
		c = '0';
	return c;
}


// Constructor.  Converts a String to a Pascal String if pascal = true.  Returns c string if false
String::String(const char *s, bool pascal) {
	len = strlen(s);
	arr = new char[len + 1];
	if (pascal == true) { 
		std::copy(s, s + len, arr);
		
	}
	else {  
		arr[0] = intToChar(len);
		
		for (int i = 1; i <= len; i++) {
			arr[i] = s[i - 1];
		}
		
		std::copy(s, s + len, arr + 1);
				
	}

}

// Copy constructor.
String::String(const String &obj) {
	len = obj.len;
	arr = new char[len + 1];
	std::copy(obj.arr, obj.arr + len + 1, arr);
}

// Move constructor.
String::String(String &&obj) {
	len = obj.len;
	arr = obj.arr;
	obj.arr = nullptr;
}

// Destructor
String::~String() {
	if (arr != nullptr)
		delete[] arr;
}

// Assignment operator
String &String::operator=(const String &rhs) {
	delete[] arr;
	len = rhs.len;
	arr = new char[len + 1];
	std::copy(rhs.arr, rhs.arr + len + 1, arr);
	return *this;
}

// Move assignment operator
String &String::operator=(String &&rhs) {
	delete[] arr;
	len = rhs.len;
	arr = rhs.arr;
	rhs.arr = nullptr;
	return *this;
}


// Mutator operator[]
char &String::operator[](int index) {
	// check whether the index is within bounds
	if (index > len || index < 0)
		throw std::out_of_range("Index is out of range");
	return arr[index];
}

// Accessor operator[]
char String::operator[](int index) const {
	// check whether the index is within bounds
	if (index > len || index < 0)
		throw std::out_of_range("Index is out of range");
	return arr[index];
}

// Get the length (number of characters) of a String object
int String::length() const {
	return len;
}

// Friend functions for == comparison
bool operator==(const String &lhs, const String &rhs) {
	if (lhs.len == 0)
		return rhs.len == 0;
	else {
		int shorter = lhs.length();
		if (rhs.length() < shorter)
			shorter = rhs.length();
		for (int i = 1; i <= shorter; i++) {
			if (lhs.arr[i] == rhs.arr[i])
				continue;
			else
				return false;
		}
		if (lhs.length() == rhs.length())
			return true;
		else
			return false;
	}
}

// Friend functions for < comparison
bool operator<(const String &lhs, const String &rhs) {
	if (lhs.len == 0) {
		return rhs.len != 0;
	}
	else {
		int shorter = lhs.length();
		if (rhs.length() < shorter)
			shorter = rhs.length();
		for (int i = 1; i <= shorter; i++) {
			if (lhs.arr[i] == rhs.arr[i])
				continue;
			else if (lhs.arr[i] < rhs.arr[i])
				return true;
			else if (lhs.arr[i] > rhs.arr[i])
				return false;
		}
		if (lhs.len == rhs.len)
			return false;
		else if (lhs.length() < rhs.length())
			return true;
		else
			return false;
	}
}


// Friend functions for > comparison
bool operator>(const String &lhs, const String &rhs) {
	return rhs < lhs;
}

// Friend functions for <= comparison
bool operator<=(const String &lhs, const String &rhs) {
	return !(rhs < lhs);
}

// Friend functions for >= comparison
bool operator>=(const String &lhs, const String &rhs) {
	return !(lhs  < rhs);
}

// Friend functions for != comparison
bool operator!=(const String &lhs, const String &rhs) {
	return !(lhs == rhs);
}

//	Friend function for string concatination
String operator+(const String &lhs, const String &rhs) {
	int strLength = lhs.len + rhs.len + 1;
	char *tmpStr = new char[strLength];
	for (auto i = 0; i < lhs.len; ++i)
		tmpStr[i] = lhs.arr[i];
	for (auto i = 0; i <= rhs.len; ++i)
		tmpStr[lhs.len + i] = rhs.arr[i];
	String retStr(tmpStr);
	delete[] tmpStr;
	return retStr;
}

// Return C style character string
const char* String::c_str() const {
	char *c_array;
	c_array = new char[len + 1];
	std::copy(arr + 1, arr + len + 1, c_array);
	return c_array;
}

//	Friend function for output
std::ostream& operator<<(std::ostream &out, const String &obj) {
	return out << obj.c_str();
}


int main() {

	String str = String("Swati", false);

	String str1 = String("5Hello", true);

	printf("str= %s \n", str);
	printf("str1= %s", str1);

	return 0;
}















