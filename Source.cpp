#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	Graph obj1;
	obj1.readGraph("graph.txt");
	char command[3];
	int from, to, weight = 0;
	cout << "���� ������� �������� � ������." << endl;
	cout << "��� ������ � ������ ����������� ��������� �������:" << endl;
	cout << "   add - ���������� �����\n   rem - �������� �����\n   cha - ��������� �����\n";
	cout << "   toM - � ������� ���������\n   toL - � ������ ���������\n   toE - � ������ �����\n";
	cout << "   wri - ������ ����� � ���� � ������� �������������" << endl;
	do {
		cin >> command;
		switch (command[0]) {
		case 'a':
			cout << "   ������: ";
			cin >> from;
			cout << "   ����:   ";
			cin >> to;
			cout << "   ���:    ";
			cin >> weight;
			obj1.addEdge(from, to, weight);
			break;
		case 'r':
			cout << "   ������: ";
			cin >> from;
			cout << "   ����:   ";
			cin >> to;
			obj1.removeEdge(from, to);
			break;
		case 'c':
			cout << "   ������: ";
			cin >> from;
			cout << "   ����:   ";
			cin >> to;
			cout << "   ���:    ";
			cin >> weight;
			cout << "������ ��� ����� " << obj1.changeEdge(from, to, weight) << "." << endl;
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
				cout << "����������� �������, ��������� ����." << endl;
			}
			break;
		case 'e':
			exit(0);
		default:
			cout << "����������� �������, ��������� ����." << endl;
		}
	} while (1);
}
