#pragma once
#include<conio.h>
#include"Snake.h"


class Observator
{
	Snake* snake;
public:
	Observator(Snake* s) {
		snake = s;
	}
	void waitForInput() // watek poboczny
	{
		while (true)
		{
			char inPut = _getch();
			snake->directionUpdate(inPut);
		}
	}
};

