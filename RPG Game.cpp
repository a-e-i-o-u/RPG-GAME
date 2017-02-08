#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Map.h"

using namespace std;

void Start();
void Print();
void getAction();
void Attack();
void Move(int, int, int, int);
void changeMap(int, int);
void Options();


struct Character {
	int yPos, xPos, hp, bronzeCoins,silverCoins,goldenCoins,Diamonds;
	Character(int yPos,int xPos,int hp) {
		this->yPos = yPos;
		this->xPos = xPos;
		this->hp = hp;
	}
}Player(4, 5, 100);

bool game_on = true,last_wasEnemy = false;
int curMap;

int main()
{
	
	cout << "WELCOME TO THE RPG GAME" << endl;
	cout << "1 - START GAME" << endl;
	cout << "2 - CONTINUE" << endl;
	cout << "3 - OPTIONS" << endl;

	char choice = _getch();

	switch (choice) {
	case '1':
		curMap = 0;
		Start();
		
		break;
	case '2':
		break;
	}
	
	
    return 0;
}
void Start() {
	Map[curMap][Player.yPos][Player.xPos] = '@';
	Print();

	while (game_on) {
		getAction();
		
	}
}
void Print() {
	system("cls");
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			if (Map[curMap][y][x] == NULL) break;
			cout << Map[curMap][y][x];
		}
		if (Map[curMap][y][0] == NULL) break;
			cout << endl;
	}
	cout << "Healthpoints: " << Player.hp << endl;
}
void getAction() {

	Move(VK_UP, 'W', Player.yPos - 1, Player.xPos);
	Move(VK_DOWN, 'S', Player.yPos + 1, Player.xPos);
	Move(VK_RIGHT, 'D', Player.yPos, Player.xPos + 1);
	Move(VK_LEFT, 'A', Player.yPos, Player.xPos - 1);
	Attack();
}
void Move(int key, int key2, int yNum, int xNum) {
	if (GetAsyncKeyState(key) || GetAsyncKeyState(key2)) {
		if (Map[curMap][yNum][xNum] != '#') {
			if(last_wasEnemy) Map[curMap][Player.yPos][Player.xPos] = '$', last_wasEnemy = false;
			else Map[curMap][Player.yPos][Player.xPos] = ' ';
			if (Map[curMap][yNum][xNum] == 'E') Player.hp -= 20, last_wasEnemy = true;
			if (Map[curMap][yNum][xNum] == 'b' || Map[curMap][yNum][xNum] == 'B' || Map[curMap][yNum][xNum] == '|' || Map[curMap][yNum][xNum] == '_') { changeMap(yNum, xNum); return; }

			Player.yPos = yNum;
			Player.xPos = xNum;
			Map[curMap][Player.yPos][Player.xPos] = '@';

			Print();
		}
	}
}
void Attack() {
	if (GetAsyncKeyState('F')) {
		if (Map[curMap][Player.yPos + 1][Player.xPos] == 'E') Map[curMap][Player.yPos + 1][Player.xPos] = '$';
		else if (Map[curMap][Player.yPos - 1][Player.xPos] == 'E') Map[curMap][Player.yPos - 1][Player.xPos] = '$';
		else if (Map[curMap][Player.yPos][Player.xPos + 1] == 'E') Map[curMap][Player.yPos][Player.xPos + 1] = '$';
		else if (Map[curMap][Player.yPos][Player.xPos - 1] == 'E') Map[curMap][Player.yPos][Player.xPos - 1] = '$';

		Print();
	}
}
void Options() {
	system("cls");


}
void changeMap(int yNum,int xNum) {
	switch (curMap) {
	case 0:
		if (Map[curMap][yNum][xNum] == 'b') {
			curMap = 1;
			Player.yPos = 2;
			Player.xPos = 1;
		}
		else if (Map[curMap][yNum][xNum] == 'B') {
			curMap = 2;
			Player.yPos = 4;
			Player.xPos = 16;
		}
		break;
	case 1:
		curMap = 0;
		Player.yPos = 6;
		Player.xPos = 2;
		break;
	case 2:
		curMap = 0;
		Player.yPos = 2;
		Player.xPos = 6;
		break;
	}
	Map[curMap][Player.yPos][Player.xPos] = '@';
	Print();
}