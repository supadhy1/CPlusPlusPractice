#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <map>

using namespace std;
int count_words(string);
string removeSpecialChars(string);
void display(map<string, int>, string);


class Node { 
private:
	char letter;
	bool marker;
	vector<shared_ptr<Node>> children;

public:
	Node() {
		letter = ' '; marker = false;
	};

	char content() {
		return letter;
	}
	void setContent(char c) {
		letter = c;
	}

	bool wordMarker() {
		return marker;
	}
	void setMarker() {
		marker = true;
	}

	shared_ptr<Node> findChild(char c) {

		for (size_t i = 0; i < children.size(); i++)
		{
			shared_ptr<Node> temp = children.at(i);
			if (temp->content() == c)
				return temp;
		}
		return nullptr;
	}

	void appendChild(shared_ptr<Node> child) {
		children.push_back(child);
	}
	vector<shared_ptr<Node>> getChildren() {
		return children;
	}
};

class Trie {
private:
	shared_ptr<Node> root;
public:
	Trie() {
		root = shared_ptr<Node>(new Node());
	};
	void addWord(string s);
	bool searchWord(string s);
};

void Trie::addWord(string s) { 
	shared_ptr<Node> curr = root;

	if (s.size() == 0) {
		curr->setMarker();
		return;
	}

	for (size_t i = 0; i < s.size(); i++) {
		shared_ptr<Node> child = curr->findChild(s[i]);

		if (child != nullptr) {
			curr = child;

		}
		else {
			shared_ptr<Node> temp = shared_ptr<Node>(new Node());
			temp->setContent(s[i]);
			curr->appendChild(temp);
			curr = temp;
		}
		if (i == s.size() - 1)
			curr->setMarker();
	}

}

bool Trie::searchWord(string s) { 
	shared_ptr<Node> curr = root;

	while (curr != nullptr)
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			shared_ptr<Node> temp = curr->findChild(s[i]);
			if (temp == nullptr)
				return false;
			curr = temp;
		}

		if (curr->wordMarker())
			return true;
		else
			return false;
	}

	return false;
}



int main()
{
	Trie* trie = new Trie();
	ifstream infile("companies.dat");
	string line;
	string fullCompanyName;

	map<string, string> synonymSet;

	if (infile.is_open()) {
		while (!infile.eof()) {
			getline(infile, line);

			stringstream ss(line);
			string primaryCompName = "";
			bool isPrimaryName = false;

			while (getline(ss, fullCompanyName, '\t')) { 
														 
				if (!isPrimaryName)
				{
					isPrimaryName = true;
					primaryCompName = removeSpecialChars(fullCompanyName); 
				}
				else
				{
					synonymSet.emplace(removeSpecialChars(fullCompanyName), primaryCompName); 
				}
				trie->addWord(removeSpecialChars(fullCompanyName)); 
			}
			ss >> line;
			
		}
		infile.close();

	}
	else {
		cout << "Unable to open companies.dat file!" << endl;

	}

	cout << "Enter a news article ending with a period symbol (.) marking the end of the article:" << endl;
	string raw_article;
	map <string, int> company_set; 

	if (getline(cin, raw_article, '.')) { 
		string article = removeSpecialChars(raw_article);
		stringstream sstr(article);
		string token = "", prev_token = "";
		bool prev_token_found = false;

		while (sstr >> token) { 
			if (trie->searchWord(token)) {
				prev_token_found = true;
				prev_token += token;
			}
			else {       
				if (prev_token_found) {
					
					if (synonymSet.count(prev_token))
						company_set[synonymSet[prev_token]]++; 
															   
					else
						company_set[prev_token]++;
					prev_token_found = false; 
					prev_token = "";
				}
			}

		}
		display(company_set, article);

	}
	cin.get();
	return 0;
	
}

int count_words(string sentence) 
{
	int wordCount = 0;
	size_t i, j;

	if (isalpha(sentence[0])) {
		wordCount++;
	}

	for (i = 1; i < sentence.length(); i++) {
		if ((isalpha(sentence[i])) && (!isalpha(sentence[i - 1])))
			wordCount++;
	}

	for (j = 1; j < sentence.length(); j++) {
		if ((!isalpha(sentence[j - 1])) && (sentence[j] == 'a') && (!isalpha(sentence[j + 1])))
			wordCount--;
		else if ((!isalpha(sentence[j - 1])) && (sentence[j] == 'a') && (sentence[j + 1] == 'n') && (!isalpha(sentence[j + 2])))
			wordCount--;
		else if ((!isalpha(sentence[j - 1])) && (sentence[j] == 'a') && (sentence[j + 1] == 'n') && (sentence[j + 2] == 'd') && (!isalpha(sentence[j + 3])))
			wordCount--;
		else if ((!isalpha(sentence[j - 1])) && (sentence[j] == 't') && (sentence[j + 1] == 'h') && (sentence[j + 2] == 'e') && (!isalpha(sentence[j + 3])))
			wordCount--;
		else if ((!isalpha(sentence[j - 1])) && (sentence[j] == 'o') && (sentence[j + 1] == 'r') && (!isalpha(sentence[j + 2])))
			wordCount--;
		else if ((!isalpha(sentence[j - 1])) && (sentence[j] == 'b') && (sentence[j + 1] == 'u') && (sentence[j + 2] == 't') && (!isalpha(sentence[j + 3])))
			wordCount--;
		else if ((!isalpha(sentence[j - 1])) && (sentence[j] == 's') && (!isalpha(sentence[j + 1])))
			wordCount--;

	}

	return wordCount;
}

string removeSpecialChars(string companyName) { 
	for (int i = 0; i < (int)companyName.size(); i++)
	{
		char c = companyName[i];
		if (!ispunct(c) && (isdigit(c) || isalpha(c))) {}

		else {
			companyName[i] = ' ';
		}
	}
	return companyName;
}

void display(map<string, int> result, string text) {
	double relevance;
	cout << endl << "Number of words in the article: " << count_words(text) << endl;

	for (map<string, int>::const_iterator it = result.begin(); it != result.end(); ++it) {
		cout << "Company Name: " << it->first;
		relevance = double(it->second / double(count_words(text))) * 100;
		cout << " Relevance: " << relevance << "%" << endl;
	}
	cout << endl;
}

