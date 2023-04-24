

#include <iostream>
#include <vector>
#include <conio.h>
#include "Game.h"

using namespace std;

int main()
{	
	Game* g = new Game();
	while (true) {
		g->draw();
		string first, second;
		first = g->read();
		if (first.size() == 0) {
			cout << "nierozpoznano elementu,zacznij od nowa\n";
			_getch();
			system("cls");
			continue;
		}
		second = g->read();
		if (second.size() == 0) {
			cout << "nierozpoznano elementu,zacznij od nowa\n";
			_getch();
			system("cls");
			continue;
		}
		g->mix(first, second);
		system("cls");
		continue;
	}
}

