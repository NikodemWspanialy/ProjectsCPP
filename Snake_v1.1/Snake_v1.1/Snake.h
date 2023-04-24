#pragma once
#include"Core.h";
#include <vector>
#include<Windows.h>
#include <cstdlib>
#include <ctime>

/// <summary>
/// aby sie nie pomylic
/// </summary>
enum Direction
{
	left, up, right, down, none
};

class Snake
{
	//mutable
	Core* board;//wskaznik na mape
	int gameSpeed = 100;//predkosc gry
	char upCh = 'w', downCh = 's', leftCh = 'a', rightCh = 'd';//klawisze ruchu

	//unmutable
	int	fruitX,//x owoca
		fruitY,//y owoca
		BoardX,//x szerokosc mapy
		BoardY,//y szerokosc mapy
		gameStatus = 0,//status gry; 0 - gramy; 1 - wygrana; -1 - przegrana, 2 - wyjscie awaryjne
		sizeCounter = 1,//dlugosc weza
		boardSize;//wielkosc mapy x*y
	std::vector<std::pair<int,int>> body; // pierwsza skladowa x, druga y
	Direction previousDir, nextDir;//aktualny kierunek podczas ruchu
	bool pause = false;//przerwa w grze guzik p domyslnie

public:
	/// <summary>
	/// konstruktor domyslny 
	/// </summary>
	/// <param name="bX"></x wielkosc mapy>
	/// <param name="bY"></y wielkosc mapy>
	/// <param name="gS"></predkosc gry>
	/// <param name="upC"></gora>
	/// <param name="downC"></dol>
	/// <param name="leftC"></lewo>
	/// <param name="rightC"></prawo>
	/// <param name="borderI"></brzgi mapy>
	/// <param name="bodyI"></pcialo>
	/// <param name="headI"></glowa>
	Snake(int bX, int bY, int gS, char upC, char downC, char leftC, char rightC, char borderI, char bodyI, char headI) : BoardX(bX), BoardY(bY), boardSize(bX*bY)
	{
		previousDir = none;
		nextDir = none;
		std::pair<int, int> head;
		head.first = bX / 2;
		head.second = bY / 2;
		body.push_back(head);

		//params
		board = new Core(bX, bY);
		board->coreSettings(borderI, bodyI, headI);
		gameSpeed = gS;
		upCh = upC;
		downCh = downC;
		leftCh = leftC;
		rightCh = rightC;
	}
	/// <summary>
	/// glowny watek gry w nim sa zawarte wszystkie kolejne metody
	/// </summary>
	int action() { //glowny watek
		fruitGen();
		while (gameStatus == 0)
		{
			pauseCheck();
			move();
			if (!ifOutOfBorder())
			{
				gameStatus = -1;
				break;
			}
			if (!ifEatTail())
			{
				gameStatus = -1;
				break;
			}
			if (ifEatFruit()) {
				gameStatus = 1;
				break;
			}
			board->putValueInFromVector(body);
			board->putValueIn(fruitX, fruitY, 70);
			system("cls");
			board->rysuj();
			//if(!sprawdz());
			Sleep(gameSpeed);
		}
		return gameStatus;
	}
	/// <summary>
	/// jezeli zjemy owoc to dodajemy go do ciala i generujemy nowy;
	///  jezeli nasza dlugosc jest rowna wielkosci mapy to wygrywamy gre
	/// </summary>
	/// <returns></returns>
	bool ifEatTail()
	{
		if (body.size() == 1)
			return 1;
		for (size_t i = 1; i < body.size(); ++i)
		{
			if (body[0].first == body[i].first and body[0].second == body[i].second)
				return 0;
		}
		return 1;
	}
	/// <summary>
	/// jezeli wyjdziemy po za mape to zwracamy 0;
	/// inacze jgramydalej i zwracamy true
	/// </summary>
	/// <returns></returns>
	bool ifOutOfBorder() {
		if (body[0].first < 0 or body[0].first >= BoardX)
			return 0;
		if (body[0].second < 0 or body[0].second >= BoardY)
			return 0;
		return 1;
	}
	/// <summary>
	/// to samo co w ifOutOfBorder tylko chodzi o nasze cialo 
	/// </summary>
	/// <returns></returns>
	bool ifEatFruit()
	{
		if (body[0].first == fruitX and body[0].second == fruitY)
		{
			sizeCounter++;
			if (sizeCounter == boardSize)
				return 1;
			std::pair<int, int> newElement;
			newElement.first = body[0].first;
			newElement.second = body[0].second;
			body.push_back(newElement);
			fruitGen();
			return 0;
		}
		return 0;
	}
	/// <summary>
	/// funkcja generuje koordynaty naszego owocka w miejscu gdzie nas nie ma;
	/// rekurencyjnie ale co zrobisz
	/// </summary>
	void fruitGen()
	{
		srand(time(NULL));
		fruitX = rand() % (BoardX);
		fruitY = rand() % (BoardY);
		if (fruitX == body[0].first and fruitY == body[0].second)
			fruitGen();
	}
	/// <summary>
	/// ma pauzowac gre w petli 
	/// </summary>
	void pauseCheck()
	{
		while (pause)
		{
			Sleep(50);
		}
	}
	/// <summary>
	/// przesuwamy wszystkie nasze segmenty o 1 i glowe w wybranym kierunku
	/// </summary>
	void move()
	{
		if (nextDir == none)
			return;
		for (size_t i = body.size(); i > 1; --i)
		{
			body[i - 1].first = body[i - 2].first;
			body[i - 1].second = body[i - 2].second;
		}
		switch (nextDir)
		{
		case up:
			previousDir = nextDir;
			body[0].first--;
			break;
		case down:
			previousDir = nextDir;
			body[0].first++;
			break;
		case left:
			previousDir = nextDir;
			body[0].second--;
			break;
		case right:
			previousDir = nextDir;
			body[0].second++;
			break;
		}
	}
	/// <summary>
	/// odbiera dane z watku obserwatora
	/// </summary>
	/// <param name="dir"></param>
	void directionUpdate(char dir)
	{
		switch (dir)
		{
		case 'w':
			if (previousDir != down)
			{
				pause = false;
				nextDir = up;
			}
			break;
		case 'a':
			if (previousDir != right)
			{
				pause = false;
				nextDir = left;
			}
			break;
		case 's':
			if (previousDir != up)
			{
				pause = false;
				nextDir = down;
			}
			break;
		case 'd':
			if (previousDir != left)
			{
				pause = false;
				nextDir = right;
			}
				break;
		case 'p':
			pause = !pause;
			break;
		case 'r':
			gameStatus = 2;
		default:
			break;
		}
	}
	~Snake() {
		delete board;
	}

};

