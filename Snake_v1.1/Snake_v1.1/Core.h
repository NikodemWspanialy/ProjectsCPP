#pragma once
#include<iostream>
#include<vector>
class Core
{
	char** board;//wskaznik na wskazik do tablicy XD
	int BoardX, BoardY;// x = cols y = rows
	char borderIcon, //znak dla borderu 
		bodyIcon, //znak dla ciala
		headIcon;//znak dla glowy weza

public:
	/// <summary>
	/// konstruktor do ustawien domyslnych i wlasnej wielkosci mapy do gry Snake
	/// </summary>
	/// <param name="row"></param>
	/// <param name="col"></param>
	Core(int x, int y) {
		borderIcon = '#';
		bodyIcon = 'o';
		headIcon = 'O';
		BoardY = y;
		BoardX = x;
		board = new char* [x];
		for (size_t i = 0; i < x; ++i)
		{
			board[i] = new char[y];
		}
		zeruj();
	}
	/// <summary>
	/// nie bylo domyslnego = byly bledy 
	/// </summary>
	Core(){}
	void coreSettings(char borderI, char bodyI, char headI) {
		borderIcon = borderI;
		bodyIcon = bodyI;
		headIcon = headI;
	}
private:
	/// <summary>
	/// czysci mape
	/// </summary>
	void zeruj() {
		for (int i = 0; i < BoardX; i++)
			for (int j = 0; j < BoardY; j++)
			{
				board[i][j] = 32;
			}
	}
public:
	/// <summary>
	/// rysuje mape i obramowki
	/// </summary>
	void rysuj() {
		for (int i = 0; i < BoardY +2; i++)
		{
			std::cout << borderIcon;
		}
		std::cout << std::endl;
		for (int i = 0; i < BoardX; i++)
		{
			for (int j = 0; j < BoardY+2; j++)
			{
				if ((j == 0) or (j == BoardY + 1))
					std::cout << borderIcon;
				else
				{
					std::cout << board[i][j-1];
				}
			}
			std::cout << std::endl;
		}
		for (size_t i = 0; i < BoardY +2; i++)
		{
			std::cout << borderIcon;
		}
		std::cout << std::endl;
	}

	char* operator[](int x)const noexcept{
		return board[x];
	}
	/// <summary>
	/// dodajemy char na element tablicy 2 wymiarowej
	/// </summary>
	/// <param name="body"></param>
	void putValueIn(int x, int y, char value = ' ') 
	{
		board[x][y] = value;
	}
	/// <summary>
	/// zwracamy wartosc z elementu talicy
	/// </summary>
	const char putValueOut(int x, int y) const noexcept
	{
		if ((x > 0 and x < BoardX) and (y > 0 and y < BoardY))
			return board[x][y];
	}
	/// <summary>
	/// to samo co wpisz wartosc ale dla vectora par gdzie first = x, second = y;
	/// </summary>
	void putValueInFromVector(std::vector<std::pair<int, int>>& body)
	{
		zeruj();
		for (auto& e : body)
		{
			board[e.first][e.second] = bodyIcon;
		}
		board[body[0].first][body[0].second] = headIcon;
		return;
	}
	~Core() {
		for (size_t i = 0; i < BoardX; ++i) {
			delete[] board[i];
		}
		delete[] board;
	}

};

