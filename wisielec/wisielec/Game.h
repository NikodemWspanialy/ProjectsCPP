#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>


using namespace std;

class Game
{
	vector<pair<char, bool>> wordToGuess;
	unsigned int lifeCounter = 9;
	vector<char> charsGuessed;
public:
	Game(string& data) {
		for (size_t i = 0; i < data.size(); i++) {
			if (data[i] == ' ') {
				pair<char, bool> p;
				p.first = data[i];
				p.second = true;
				wordToGuess.push_back(p);
			}
			else {
				pair<char, bool> p;
				p.first = data[i];
				p.second = false;
				wordToGuess.push_back(p);
			}
		}
	}
	bool Guess(char& guesseeChar) {
		if (guesseeChar == ' ') {
			return false;
		}
		bool somethingIsGuessed = false;
		for (auto& x : wordToGuess) {
			if (x.first == guesseeChar) {
				x.second = true;
				if (somethingIsGuessed == false)
					somethingIsGuessed = true;
			}
		}
		if (somethingIsGuessed == false) {
			charsGuessed.push_back(guesseeChar);
			lifeCounter--;
		}
		for (auto x : wordToGuess) {
			if (x.second == false)
				return false;
		}
		return true;
	}
	string ToString() {
		string word = "";
		for (auto x : wordToGuess) {
			if (x.second == true)
				word += x.first;
			else
				word += "_";
		}
		return word;
	}
	string ToStringTrue() {
		string word = "";
		for (auto x : wordToGuess) {
			word += x.first;
		}
		return word;
	}
	int getLifeCounter() {
		return lifeCounter;
	}
	string tryGeuessFalseToString() {
		string charsgeuessedString = "";
		for (auto x : charsGuessed) {
			charsgeuessedString += x;
			charsgeuessedString += ' ';
		}
		return charsgeuessedString;
	}
	bool CheckGuessedFalse(char x) {
		for (auto ch : charsGuessed) {
			if (ch == x)
				return false;
		}
		return true;
	}
};

