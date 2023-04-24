#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "DevelopedClass.h"
#include "define.h"
#include <conio.h>
#include<fstream>
#include<sstream>

using namespace std;

class Game
{
	vector<vector<string>> cookBook;
	Developed developed;
	int countElements = 300;
public:
	Game(){
		string x = "";
		fstream file;
		stringstream ss;
		vector<string> temp;
		file.open("cookBook.txt");
		if (file.is_open()) {
			while (getline(file, x)) {
				string a = "", b = "", c = "", d = "", e = "", f = "", g = "", h = "", i = "", number = "";
				ss << x;
				ss >> number >> a >> b >> c >> d >> e >> f >> g >> h >> i;
				temp.push_back(c);
				temp.push_back(e);
				temp.push_back(a);
				cookBook.push_back(temp);
				temp.pop_back();
				temp.pop_back();
				temp.pop_back();
				if (f.size() != 0) {
					temp.push_back(g);
					temp.push_back(i);
					temp.push_back(a);
					cookBook.push_back(temp);
					temp.pop_back();
					temp.pop_back();
					temp.pop_back();
				}
				//a = ""; b = ""; c = ""; d = ""; e = ""; f = ""; g = ""; h = ""; i = "";
				x = "";
				ss.clear();
			}
		}
		file.close();
	/*	for (int i = 0; i < cookBook.size(); i++) {
			cout << cookBook[i][0] << " " << cookBook[i][1] << " " << cookBook[i][2] << endl;
		}*/
	}

	void draw() {
		developed.WriteDown(countElements);
		std::cout << "----------------------------------------------------\nCo chesz zmieszac?\n";
	}

	string read() {
		string x;
		cin >> x;
		for (string e : developed.dev)
		{
			if (x == e)
				return x;
		}
		return "";
	}	


	void mix(string x, string y) {
		for (int i = 0; i < cookBook.size(); i++) {
			if (x == cookBook[i][0] and y == cookBook[i][1] or x == cookBook[i][1] and y == cookBook[i][0]) {
				developed.AddElement(cookBook[i][2]);
				cout << "Wlasnie odkryles: " << cookBook[i][2] << endl;
				_getch();
				return;
			}
		}
			cout << "nic nie odkryles" << endl;
			_getch();
			return;
	}
};

