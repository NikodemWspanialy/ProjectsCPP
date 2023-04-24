//lobby tymczaskowe, plan jest aby zrobic fajne lobby z ustawieniami i guzikiem na replay i na start wgl
//to tylko odpala gre i nic wieej nie robi w sumie
#pragma once


#include "Snake.h"
#include <iostream>
#include<thread>
#include"Observator.h"


class Lobby
{
	Snake* snake;


public:
	Lobby()
	{
		lobbySnake();
	}
	void lobbySnake()
	{
		snake = new Snake(20, 50, 100, 'w', 's', 'a', 'd','#','o','O');
		Observator* obs = new Observator(snake);
		std::thread thr1(&Lobby::playSnake, this);
		std::thread thr2(&Observator::waitForInput, obs);
		thr2.detach();
		thr1.join();
		thr2.~thread();
		delete(obs);
	}
private:
	void playSnake() {
		int i = snake->action();
		if (i == -1)
			std::cout << "przegrales!\n";
		else if (i == 1)
			std::cout << "Wygrales!\n";
		return;
	}
	~Lobby() {
		delete snake;
	}
};

