#include "Graph.h"

void Graph::readGraph(string fileName)
{
	ifstream fin(fileName);
	char symbol;
	fin >> symbol >> size;
	switch (symbol)
	{
	case 'C':
		fin >> oriented >> weighted;
		representation = ADJ_MATRIX;
		adjMatrix.assign(size + 1, vector<int>(size + 1, 0));
		for (int i = 1; i <= size; i++)
			for (int j = 1; j <= size; j++)
				fin >> adjMatrix[i][j];
		break;
	case 'L':
		fin >> oriented >> weighted;
		representation = ADJ_LIST;
		adjList.resize(size + 1);
		fin.ignore();
		for (int i = 1; i <= size; i++)
		{
			string line;
			getline(fin, line);
			stringstream ss(line);
			int b, w;
			if (weighted)
				while (ss >> b >> w)
					adjList[i][b] = w;
			else
				while (ss >> b)
					adjList[i][b] = 1;
		}
		break;
	case 'E':
		representation = EDGES_LIST;
		fin >> numOfEdges >> oriented >> weighted;
		int from, to, weight;
		for (int i = 0; i < numOfEdges; i++)
		{
			fin >> from >> to;
			if (weighted)
			{
				fin >> weight;
				edgesList[make_pair(from, to)] = weight;
			}
			else
				edgesList[make_pair(from, to)] = 1;
		}
		break;
	default:
		cout << "Ошибка: Неизвестный формат представления.";
		exit(1);
	}
	fin.close();
}

void Graph::addEdge(int from, int to, int weight = 1)
{
	switch (representation)
	{
	case ADJ_MATRIX:
		if (!weighted)
			weight = 1;
		if (adjMatrix[from][to])
			cout << "Ребро уже существует." << endl;
		else
		{
			adjMatrix[from][to] = weight;
			if (!oriented)
				adjMatrix[to][from] = weight;
		}
		break;
	case ADJ_LIST:
		if (!weighted)
			weight = 1;
		if (adjList[from][to])
			cout << "Ребро уже существует." << endl;
		else
		{
			adjList[from][to] = weight;
			if (!oriented)
				adjList[to][from] = weight;
		}
		break;
	case EDGES_LIST:
		if (!weighted)
			weight = 1;
		if (edgesList[make_pair(from, to)])
		{
			cout << "Ребро уже существует." << endl;
		}
		else
		{
			edgesList[make_pair(from, to)] = weight;
			if (!oriented)
				edgesList[make_pair(to, from)] = weight;
		}
		break;
	}
}

void Graph::removeEdge(int from, int to)
{
	switch (representation)
	{
	case ADJ_MATRIX:
		adjMatrix[from][to] = 0;
		if (!oriented)
			adjMatrix[to][from] = 0;
		break;
	case ADJ_LIST:
		adjList[from].erase(to);
		if (!oriented)
			adjList[to].erase(from);
		break;
	case EDGES_LIST:
		edgesList.erase(make_pair(from, to));
		if (!oriented)
			edgesList.erase(make_pair(to, from));
		break;
	}
}

int Graph::changeEdge(int from, int to, int newWeight = 1)
{
	int oldWeight = 0;
	if (!weighted)
	{
		cout << "Нельзя изменять вес ребра невзвешенного графа." << endl;
	}
	else
	{
		switch (representation) {
		case ADJ_MATRIX:
			oldWeight = adjMatrix[from][to];
			if (oldWeight)
			{
				adjMatrix[from][to] = newWeight;
				if (!oriented)
					adjMatrix[to][from] = newWeight;
			}
			else
				cout << "Нельзя изменять вес несуществующего ребра." << endl;
			break;
		case ADJ_LIST:
			if (adjList[from].count(to))
			{
				oldWeight = adjList[from][to];
				adjList[from][to] = newWeight;
				if (!oriented)
					adjList[to][from] = newWeight;
			}
			else
			{
				oldWeight = 0;
				cout << "Нельзя изменять вес несуществующего ребра." << endl;
			}
			break;
		case EDGES_LIST:
			if (edgesList.count(make_pair(from, to)))
			{
				oldWeight = edgesList[make_pair(from, to)];
				edgesList[make_pair(from, to)] = newWeight;
				if (!oriented)
					edgesList[make_pair(to, from)] = newWeight;
			}
			else
			{
				oldWeight = 0;
				cout << "Нельзя изменять вес несуществующего ребра." << endl;
			}
			break;
		}
	}
	return oldWeight;
}

void Graph::transformToAdjList()
{
	adjList.assign(size + 1, map <int, int>());
	switch (representation)
	{
	case ADJ_MATRIX:
		for (int i = 1; i <= size; i++)
			for (int j = 1; j <= size; j++)
				if (adjMatrix[i][j])
					adjList[i][j] = adjMatrix[i][j];
		adjMatrix.clear();
		break;
	case EDGES_LIST:
		for (auto it : edgesList)
		{
			adjList[it.first.first][it.first.second] = it.second;
		}
		edgesList.clear();
		break;
	}
	representation = ADJ_LIST;
}
void Graph::transformToAdjMatrix()
{
	adjMatrix.assign(size + 1, vector<int>(size + 1, 0));
	switch (representation)
	{
	case ADJ_LIST:
		for (int i = 1; i <= size; i++)
			for (auto it : adjList[i])
				adjMatrix[i][it.first] = it.second;
		adjList.clear();
		break;
	case EDGES_LIST:
		for (auto it : edgesList)
		{
			adjMatrix[it.first.first][it.first.second] = it.second;
		}
		edgesList.clear();
		break;
	}
	representation = ADJ_MATRIX;
}
void Graph::transformToListOfEdges()
{
	numOfEdges = 0;
	switch (representation)
	{
	case ADJ_MATRIX:
		for (int i = 1; i <= size; i++)
			for (int j = 1; j <= size; j++)
				if (adjMatrix[i][j])
				{
					edgesList[make_pair(i, j)] = adjMatrix[i][j];
					numOfEdges++;
				}
		adjMatrix.clear();
		break;
	case ADJ_LIST:
		for (int i = 1; i <= size; i++)
			for (auto it : adjList[i])
			{
				edgesList[make_pair(i, it.first)] = it.second;
				numOfEdges++;
			}
		adjList.clear();
		break;
	}
	representation = EDGES_LIST;
}
void Graph::writeGraph(string fileName)
{
	ofstream fout(fileName);
	switch (representation)
	{
	case ADJ_MATRIX:
		fout << "C " << size << endl << (oriented ? 1 : 0) << ' ' << (weighted ? 1 : 0) << endl;
		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j <= size; j++)
				fout << adjMatrix[i][j] << " ";
			fout << endl;
		}
		break;
	case ADJ_LIST:
		fout << "L " << size << endl << (oriented ? 1 : 0) << ' ' << (weighted ? 1 : 0) << endl;
		for (int i = 1; i <= size; i++)
		{
			for (auto it : adjList[i])
			{
				fout << it.first << ' ';
				if (weighted)
					fout << it.second << ' ';
			}
			fout << endl;
		}
		break;
	case EDGES_LIST:
		fout << "E " << size << ' ' << edgesList.size() << endl;
		fout << (oriented ? 1 : 0) << ' ' << (weighted ? 1 : 0) << endl;
		for (auto it : edgesList)
		{
			fout << it.first.first << ' ' << it.first.second;
			if (weighted)
				fout << ' ' << it.second;
			fout << endl;
		}
		break;
	}
	fout.close();
}