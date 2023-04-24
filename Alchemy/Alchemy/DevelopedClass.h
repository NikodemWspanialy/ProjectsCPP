#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

class Developed {
public:
	vector<string> dev;
	Developed() {
		dev.push_back("woda");
		dev.push_back("powietrze");
		dev.push_back("ogien");
		dev.push_back("ziemia");
	}
	void AddElement(const string e) {
		for (string x : dev) {
			if (x == e)
				return;
		}
		dev.push_back(e); 
	}
    void WriteDown(int countElements) {
		int setwsize = 25;
		if (dev.size() == countElements) {
			cout << "\nOdkryles wszystko!\n\n";
		}
		sort(dev.begin(), dev.end());
		for (int i = 0; i < dev.size() / 3; i++) {
			cout << setw(setwsize) << dev[i] << setw(setwsize) << dev[i + 1] << setw(setwsize) << dev[i + 2] << endl;
		}
		if (dev.size() % 3 == 1) {
			cout << setw(setwsize) << dev[dev.size() - 1] << endl;
		}
		if (dev.size() % 3 == 2) {
			cout << setw(setwsize) << dev[dev.size() - 2] << setw(setwsize) << dev[dev.size() - 1] << endl;
		}
	}
};