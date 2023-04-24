#include <string>
#include <iostream>
#include "Game.h"
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include<cstdlib>

using namespace std;

char charCin(Game* game) {
    char x = _getch();
    if (isalpha(x) and game->CheckGuessedFalse(x))
        return x;
    return ' ';
}
bool rounds(Game* game) {
    game->ToString();
    char guess = charCin(game);
    bool win = game->Guess(guess);
    return win;
}
string randomWord() {
    fstream plik;
    string s;
    vector<string> v;
    plik.open("words.txt");
    if (plik.is_open()) {
        while (getline(plik, s)) {
            v.push_back(s);
        }
    }
    int random = rand() % v.size();
    return v[random];
}
void menu() {
    srand((unsigned)time(NULL));
    string word = randomWord();
    Game* game = new Game(word);
    bool gameStatus;
    do {
        int life = game->getLifeCounter();
        {
            cout << "ilosc zyc : " << life << endl;

        }
        if (game->tryGeuessFalseToString() != "") {
            cout << "prubowales zgadnac : " << game->tryGeuessFalseToString() << endl;
        }
        cout << game->ToString() << endl;
        if (life == 0) {
            cout << "przegrales!\nPprawne haslo to : " << game->ToStringTrue() << endl
                << "czy chcesz zagrac jeszcze raz? t/n\n";
            char replay = _getch();
            if (replay == 't') {
                system("cls");
                menu();
            }
            delete game;
            return;
        }
        gameStatus = rounds(game);
        system("cls");
    } while (gameStatus == false);
    cout << "brawo odgadles haslo : " << game->ToStringTrue() << "\ngramy jeszcze raz? t/n\n";
    char replay = _getch();
    if (replay == 't') {
        system("cls");
        menu();
    }
    delete game;
    return;
}
int main()
{
    menu();
}
