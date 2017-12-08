#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	Graph obj1;
	obj1.readGraph("graph.txt");
	char command[3];
	int from, to, weight = 0;
	cout << "Граф успешно загружен в память." << endl;
	cout << "Для работы с графом используйте следующие команды:" << endl;
	cout << "   add - добавление ребра\n   rem - удаление ребра\n   cha - изменение ребра\n";
	cout << "   toM - в матрицу смежности\n   toL - в список смежности\n   toE - в список ребер\n";
	cout << "   wri - запись графа в файл в текущем представлении" << endl;
	do {
		cin >> command;
		switch (command[0]) {
		case 'a':
			cout << "   откуда: ";
			cin >> from;
			cout << "   куда:   ";
			cin >> to;
			cout << "   вес:    ";
			cin >> weight;
			obj1.addEdge(from, to, weight);
			break;
		case 'r':
			cout << "   откуда: ";
			cin >> from;
			cout << "   куда:   ";
			cin >> to;
			obj1.removeEdge(from, to);
			break;
		case 'c':
			cout << "   откуда: ";
			cin >> from;
			cout << "   куда:   ";
			cin >> to;
			cout << "   вес:    ";
			cin >> weight;
			cout << "Старый вес ребра " << obj1.changeEdge(from, to, weight) << "." << endl;
			break;
		case 'w':
			obj1.writeGraph("graph.txt");
			break;
		case 't':
			switch (command[2])
			{
			case 'M':
				obj1.transformToAdjMatrix();
				break;
			case 'L':
				obj1.transformToAdjList();
				break;
			case 'E':
				obj1.transformToListOfEdges();
				break;
			default:
				cout << "Неизвестная команда, повторите ввод." << endl;
			}
			break;
		case 'e':
			exit(0);
		default:
			cout << "Неизвестная команда, повторите ввод." << endl;
		}
	} while (1);
}
