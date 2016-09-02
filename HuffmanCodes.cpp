#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct symbol_info
{
	char symbol;
	int frequency;
};

struct tree_node
{
	char symbol;
	int frequency;
	struct tree_node *left;
	struct tree_node *right;
	tree_node(char x, int y) { symbol = x; frequency = y; left = NULL; right = NULL; };
};

class comparator {
public:
	bool operator () (tree_node *t1, tree_node *t2)
	{
		return (t1->frequency > t2->frequency);
	}
};


int createInfile(string inputFileName, string outputFileName) {
	char c;
	ifstream inputFile(inputFileName);
	ofstream outputFile(outputFileName);
	if (inputFile.fail() || outputFile.fail())
	{
		return 0;
	}
	else {

		while (inputFile.get(c))
		{
			if (!ispunct(c) && (isdigit(c) || isalpha(c))) {
				outputFile << c;
			}
		}
		inputFile.close();
		outputFile.close();
		return 1;
	}
}

ofstream outfile("outfile.dat");
int messageSize = 0;

void displayHCodes(tree_node *top, string code)
{

	if (!top)
		return;
	if (top->symbol != '\0')
	{
		int stringLength = code.size();
		messageSize = messageSize + stringLength * top->frequency;
		outfile << top->symbol << "\t\t\t" << top->frequency << "\t\t\t" << code << "\n";
	}
	displayHCodes(top->left, code + "0");
	displayHCodes(top->right, code + "1");
}


int main() {

	char symbol[100] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
	vector<symbol_info> SymbolVector;

	string inputTextFileName;
	int flag = createInfile("infile.dat", "temp.dat");
	if (flag != 0)
	{
		ifstream infile("temp.dat");
		char infChar, temp;
		if (infile.fail()) {
			cout << "File cannot be opened" << endl;
			return 0;
		}
		else {
			while (infile.get(infChar))
			{
				for (int i = 0; i < 62; i++)
				{
					temp = symbol[i];
					SymbolVector.push_back(symbol_info());
					SymbolVector[i].symbol = symbol[i];
					if (infChar == temp)
					{
						SymbolVector[i].frequency++;
						break;
					}
				}
			}
			SymbolVector.push_back(symbol_info());

			std::priority_queue<tree_node *, vector<tree_node *>, comparator> FOREST;
			for (int i = 0; i < 62; i++)
			{
				if (SymbolVector[i].frequency != 0)
				{
					FOREST.push(new tree_node(SymbolVector[i].symbol, SymbolVector[i].frequency));
				}
			}
			// Generating huffmann tree.
			while (FOREST.size()>1)
			{
				tree_node *least = FOREST.top();
				FOREST.pop();
				tree_node *second = FOREST.top();
				FOREST.pop();
				int newRootFrequency = least->frequency + second->frequency;
				tree_node * forest_roots = new tree_node('\0', newRootFrequency);
				forest_roots->left = least;
				forest_roots->right = second;
				FOREST.push(forest_roots);
			}
			if (outfile.fail()) {
				cout << "Cannot Write to file";
				return 0;
			}
			else
			{
				outfile << "Character" << "\t\t" << "Frequency" << "\t\t" << "Huffman Code" << endl;
				outfile << "---------" << "\t\t" << "---------" << "\t\t" << "------------" << endl;
				displayHCodes(FOREST.top(), string(""));
				outfile << endl;
				outfile << "Size of Huffman code is : " << messageSize << " bits " << endl;
				infile.close();
				outfile.close();
			}
			remove("temp.dat");
			ifstream displayOutFile("outfile.dat");
			if (displayOutFile.fail()) {
				cout << "Unable to open outfile.dat file**" << endl;
				return 0;
			}
			else
			{
				while (displayOutFile.get(infChar))
				{
					cout << infChar;
				}
			}

		}
	}
	else {
		cout << "Cannot find infile.dat" << endl;
	}

	cin.get();
	return 0;
}