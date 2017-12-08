#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <map>

using namespace std;

class Graph
{
public:
	enum type { ADJ_MATRIX, ADJ_LIST, EDGES_LIST };

	void readGraph(string fileName);
	void addEdge(int from, int to, int weight);
	void removeEdge(int from, int to);
	int changeEdge(int from, int to, int newWeight);
	void transformToAdjList();
	void transformToAdjMatrix();
	void transformToListOfEdges();
	void writeGraph(string fileName);

private:
	type representation;
	unsigned int size, numOfEdges;
	bool oriented, weighted;
	vector <vector <int> > adjMatrix;
	vector < map<int, int> > adjList;
	map<pair<int, int>, int> edgesList;
};

