//FINAL PROJECT

#include <fstream>
#include <functional>
#include <climits>
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <map>
#include <algorithm>

using std::ifstream;
using std::map;
using std::cout;
using std::endl;
using std::istringstream;
using std::vector;
using std::pair;
using std::string;
using std::list;

typedef map< string, int > mapping;
typedef vector< int > degrees;

using namespace std;

class Graphs
{
	struct node {
		int vertex;
		int weight;
		node(int v, int w) : vertex(v), weight(w) { };
		node() { }
	};

	class CompareGreater {
	public:
		bool const operator()(node &nodeU, node &nodeV) {
			return (nodeU.weight > nodeV.weight);
		}
	};

public:

	map< string, mapping > data; //store node and weight
	map< int, degrees> nodeDegree; //to store vertex, in degree and out degree
	vector< list<node> > adj; //adjacency list for shortest path
	vector<int> weights;
	vector<int> vertices;
	vector<vector<string>> matrixOutput; //to store the ASCII art
	map<int, int> vertexIndex; //location of vertex in ASCII art
	int nVertices, nEdges; //total number of vertices and edges

	void readData() {

		ifstream inputFile("graph.dat", ifstream::binary);
		string currentLine;
		nEdges = 0;
		while (getline(inputFile, currentLine))
		{
			if (currentLine.length() == 0)
				break;
			istringstream lineInputStream(currentLine);
			string node, destination, str;
			int length;
			int vertice;
			lineInputStream >> node;
			str = node;
			istringstream(str) >> vertice;
			while (lineInputStream >> destination)
			{
				length = 0;
				if (lineInputStream >> length)
				{
					if (data.find(node) == data.end())//data stores the source node
					{
						str = node;
						istringstream(str) >> vertice;

						if (find(vertices.begin(), vertices.end(), vertice) == vertices.end())
						{
							vertices.push_back(vertice); //to calculate number of vertices
						}
						degrees newDegree;
						mapping newMapping;
						data.insert(pair< string, mapping >(node, newMapping));

						if (nodeDegree.find(vertice) == nodeDegree.end())
						{

							nodeDegree.insert(pair< int, degrees>(vertice, newDegree));
							nodeDegree[vertice].push_back(0); //indegree
							nodeDegree[vertice].push_back(0); //outdegree
						}


					}

					data[node].insert(pair< string, int >(destination, length)); //stores destination and length

					str = destination;
					istringstream(str) >> vertice;

					if (find(vertices.begin(), vertices.end(), vertice) == vertices.end()) //to add unexplicitly mentioned vertices
					{
						vertices.push_back(vertice);
						if (nodeDegree.find(vertice) == nodeDegree.end()) {

							degrees newDegree;
							nodeDegree.insert(pair< int, degrees>(vertice, newDegree));
							nodeDegree[vertice].push_back(0); 
							nodeDegree[vertice].push_back(0); 
						}
					}

				}
				else
				{
					cout << "dijkstra format error. exit." << endl;
				}
			}
		}
		inputFile.close();

		for (auto dataIt = data.begin(); dataIt != data.end(); ++dataIt)
		{
			mapping& currentMapping = dataIt->second;
			for (auto mappingIt = currentMapping.begin(); mappingIt != currentMapping.end(); ++mappingIt)
			{

				++nEdges;
				for (auto nodeIt = nodeDegree.begin(); nodeIt != nodeDegree.end(); ++nodeIt) {

					int od;
					string str = dataIt->first;
					istringstream(str) >> od;
					if (nodeIt->first == od) {
						nodeDegree[od].at(1)++;
					}

					int id;
					string str1 = mappingIt->first;
					istringstream(str1) >> id;
					if (nodeIt->first == id) {
						nodeDegree[id].at(0)++;
					}
				}
			}
		}

		nVertices = (int)vertices.size();

		asciiPrint();
		printMatrix();
		cout << endl;
		cout << endl;
		cout << "---------------------Shortest Paths--------------------------" << endl;
		cout << endl;
		

	}

	void asciiPrint()
	{

		/*---------------to print the vertices in the ASCII art------------------------------------*/

		vector<string> rowValue;
		for (auto it = nodeDegree.begin(); it != nodeDegree.end(); ++it) 
		{
			rowValue.push_back("[");
			string input = to_string(it->first);
			rowValue.push_back(input);
			vertexIndex.insert(pair<int, int>(it->first, rowValue.size() - 1));
			rowValue.push_back("]");
			rowValue.push_back(" ");
			rowValue.push_back(" ");
			rowValue.push_back(" ");
			rowValue.push_back(" ");
			rowValue.push_back(" ");
			rowValue.push_back(" ");
			rowValue.push_back(" ");
			rowValue.push_back(" ");
		}

		matrixOutput.push_back(rowValue);
		asciiMatrix(); //to create an empty ASCII art

		cout << "--------------------------ASCII Art Graph ------------------------------" << endl;
		cout << endl;

		/*---------------to print the edges in the ASCII art------------------------------------*/

		int increment = 0;
		for (auto dataIt = data.begin(); dataIt != data.end(); ++dataIt)
		{
			mapping& currentMapping = dataIt->second;
			int i = 0, o = 0;

			for (auto mappingIt = currentMapping.begin(); mappingIt != currentMapping.end(); ++mappingIt)
			{
				/*dataIt->first will display the source, mappingIt->second - the weight, mappingIt->first the destination */

				if (vertexIndex.find(stoi(dataIt->first)) != vertexIndex.end())
				{
					o = vertexIndex[stoi(dataIt->first)];
				}
				if (vertexIndex.find(stoi(mappingIt->first)) != vertexIndex.end())
				{
					i = vertexIndex[stoi(mappingIt->first)];
				}

				//o is the index of source and i is the index of destination in matrix
				if (o != 0 && i != 0) {
					for (int p = 1; p <= 4; p++)
					{
						string weight = to_string(mappingIt->second);
						int len = (int)weight.length();
						len = len - 1;

						for (int r = 1; r<p + increment; r++)
						{

							if (matrixOutput[r].at(o) == "-")
							{
								matrixOutput[r].at(o) = "=";
							}
							if (matrixOutput[r].at(i) == "-")
							{
								matrixOutput[r].at(i) = "=";
							}
							if (matrixOutput[r].at(o) != "+" && matrixOutput[r].at(o) != "=")
							{
								matrixOutput[r].at(o) = "|";
							}
							if (matrixOutput[r].at(i) != "+" && matrixOutput[r].at(i) != "=")
							{
								matrixOutput[r].at(i) = "|";
							}

						}
						if (p == 4) //line of edge
						{
							if (o>i)
							{
								matrixOutput[p + increment].at(o - len) = "+";
								matrixOutput[p + increment].at(i) = "+";

								for (int q = i + 1; q<o - len; q++)
								{
									if (matrixOutput[p + increment].at(q) == "-")
									{
										matrixOutput[p + increment].at(q) = "=";
									}
									else
									{
										matrixOutput[p + increment].at(q) = "-";
									}
								}
								matrixOutput[p + increment].at((i + 1) + (o - i) / 2) = weight;
								matrixOutput[p + increment].at((i - 1) + (o - i) / 2) = "<";
							}
							else
							{
								matrixOutput[p + increment].at(o) = "+";
								matrixOutput[p + increment].at(i - len) = "+";
								for (int q = o + 1; q<i - len; q++)
								{
									if (matrixOutput[p + increment].at(q) == "-")
									{
										matrixOutput[p + increment].at(q) = "=";
									}
									else
									{
										matrixOutput[p + increment].at(q) = "-";
									}
								}
								matrixOutput[p + increment].at((o + 1) + (i - o) / 2) = weight;
								if (matrixOutput[p + increment].at((o + 3) + (i - o) / 2) == "+") {
									matrixOutput[p + increment].at((o + 2) + (i - o) / 2) = ">";

								}
								else
								{
									matrixOutput[p + increment].at((o + 3) + (i - o) / 2) = ">";
								}

							}
						}
					}
				}

				increment += 4; //to keep a gap between edges

			}
		}


	}
	void asciiMatrix() //to create a matrix based on the number of vertices and edges
	{
		int i = (int)matrixOutput[0].size(); //row length
		for (int x = 0; x < (4 * nEdges); x++) {
			vector<string> rowValue;
			for (int y = 0; y<i; y++) {
				rowValue.push_back(" ");
			}
			matrixOutput.push_back(rowValue);
		}

	}

	void printMatrix()// to printout the ASCII art
	{
		for (int i = 0; i<matrixOutput.size(); i++) {
			for (int j = 0; j<matrixOutput[i].size(); j++) {

				cout << matrixOutput.at(i).at(j);
			}
			cout << endl;
		}
	}



	void setAdjacencyList() //creating adjacency list
	{

		vector<int>::iterator iter;
		for (iter = vertices.begin(); iter != vertices.end(); iter++)
		{

			//to print the output from vertex
			cout << "For vertex " << *iter << " (weights): ";
			int nodeU, nodeV, weight;
			string str;

			adj.resize(nVertices + 1);
			weights.resize(nVertices + 1);

			for (int i = 1; i <= nVertices; ++i) {
				weights.at(i) = INT_MAX;
			}

			for (auto dataIt = data.begin(); dataIt != data.end(); ++dataIt)
			{
				mapping& currentMapping = dataIt->second;
				for (auto mappingIt = currentMapping.begin(); mappingIt != currentMapping.end(); ++mappingIt)
				{
					str = dataIt->first;
					istringstream(str) >> nodeU;
					str = mappingIt->first;
					istringstream(str) >> nodeV;
					weight = mappingIt->second;
					adj[nodeU].push_back(node(nodeV, weight));

				}
			}
			vector<int> previous;
			previous = Dijkstra(node(*iter, 0));
			writeData(previous, *iter);
		}
	}


	vector<int> Dijkstra(node startNode)
	{
		priority_queue<node, vector<node>, CompareGreater> Q;
		node currentNode;
		vector<int> innerSSSP;
		int n = (int)adj.size();

		innerSSSP.clear();
		innerSSSP.resize(n, -1);

		weights[startNode.vertex] = 0;
		Q.push(startNode);

		while (!Q.empty())
		{
			currentNode = Q.top();

			Q.pop();
			if (currentNode.weight <= weights[currentNode.vertex]) {

				for (list<node>::iterator it = adj[currentNode.vertex].begin(); it != adj[currentNode.vertex].end(); ++it) {

					if (weights[it->vertex] > weights[currentNode.vertex] + it->weight) {
						weights[it->vertex] = weights[currentNode.vertex] + it->weight;
						innerSSSP[it->vertex] = currentNode.vertex;
						Q.push(node((it->vertex), weights[it->vertex]));

					}
				}
			}

		}

		return innerSSSP;

	}

	void writeData(vector<int> &previous, int startNode)
	{

		weights.resize(nVertices + 1);
		for (vector<int>::iterator it = weights.begin() + 1; it != weights.end(); ++it) {
			if (*it == INT_MAX) {
				cout << "0" << " ";
			}
			else
			{
				cout << (*it) << " ";

			}


		}
		cout << endl;
		cout << "-------------------------";
		cout << endl;

		//my count checks if the there exists actual weight from node
		long myCount = count_if(weights.begin(), weights.end(), [](int i) {if (i == INT_MAX) { return true; } else { return false; }});

		if (myCount == (nVertices - 1)) {
			cout << "no paths exist from vertex" << endl;
			cout << endl;
			cout << endl;
		}
		else
		{
			vector<int>::iterator iter;
			for (iter = vertices.begin(); iter != vertices.end(); iter++)
			{
				list<int> path = shortestPath(*iter, previous);
				cout << "shortest path from " << startNode << " to " << *iter << ":" << endl;
				if (startNode == *iter) {
					cout << "source and destination is the same." << "\n" << "Path does not exist!" << endl;
				}
				else
				{
					list<int>::iterator i;
					for (i = path.begin(); i != path.end(); ++i)
					{
						if (*i == startNode) {
							cout << *i;
						}
						else
						{
							cout << "--->";
							cout << *i;
						}

					}
					cout << endl;

				}
				cout << endl;
			}
			cout << endl;
			cout << endl;

		}


	}

	list<int> shortestPath(int vertex, const vector<int> &previous)
	{
		list<int> path;
		for (; vertex != -1; vertex = previous[vertex])
			path.push_front(vertex);
		return path;
	}



};
int main(int argc, char *argv[]) {
	Graphs g;
	g.readData();
	g.setAdjacencyList();
	system("pause");
	return 0;
}