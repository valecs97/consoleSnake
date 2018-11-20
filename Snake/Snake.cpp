// Snake.cpp : Defines the entry point for the console application.
//
// A SE STERGE TOATA MUTAREA 
// NUMAI CAPUL SE MISCA , ALEA CU CAPU IS BUNE ... DAR COADA RETINEO INTRO MATRICE , UITATE PE HARTIE CUM SA O RETII

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <stdlib.h> 

using namespace std;

int xTail,yTail,xHead,yHead; // position of snake tail and head
int posWalls[200][200]; // remember where are the walls for easier
int columns, rows; // remember the console columns and rows
int notDead = 1; // check if the snake is dead or not
int Score; // Your Score
char direction='d',lastDirection; // in which direction is the snake going ? w = up , a=left, s=down, d=right
bool changed = FALSE; // do not let multiple keys being pressed
int bonusTime; // time till the next bonus



void getConsole();
void makeWalls(int columns,int rows);
void createSnake(int columns, int rows);
void changeDirection();
void move(int x , int y);
void run();
void update();
void deleteTail();
void generateFood();
void gameOver();
void showScore();
void generateBonus();

void getConsole()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	makeWalls(columns, rows);
}

void makeWalls(int columns, int rows)
{
	for (int i = 1; i <= columns; i++){
		cout << char(219);
		posWalls[0][i - 1] = -1;
	}
	for (int i = 2; i <= rows; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { columns-1, i-1 });
		cout << char(219);
		posWalls[i - 1][columns - 1] = -1;
	}
	for (int i = 2; i <= columns; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { i-1, rows-1 });
		cout << char(219);
		posWalls[rows - 1][i - 1] = -1;
	}
	for (int i = 2; i <= rows; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, i-1 });
		cout << char(219);
		posWalls[i - 1][0] = -1;
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
}

void createSnake()
{
	xTail = columns/2 - 2;
	yTail = rows / 2;
	xHead = columns / 2 + 1;
	yHead = rows / 2;
	for (int i = xTail; i < xHead; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { i, yHead });
		posWalls[yHead][i] = 'd';
		cout << "0";
	}
	posWalls[yHead][xHead] = 'd';
	cout << "1";
}

void changeDirection()
{
	while (notDead)
	{
		if (changed){
			char tmp;
			tmp = _getch();
			if (tmp < 97)tmp += 32;
			if (direction == 'w' || direction == 's')
				if (tmp == 'a' || tmp == 'd')
					direction = tmp;
			if (direction == 'a' || direction == 'd')
				if (tmp == 'w' || tmp == 's')
					direction = tmp;
			changed = FALSE;
		}
	}
}

void showScore()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 70, 0 });
	cout << "Score:" << Score;
}

void deleteTail()
{
	bool ok = TRUE;
	switch (posWalls[yTail][xTail])
	{
	case 'a':
	{
		if (posWalls[yTail][xTail - 1] == 'a')
		{
			posWalls[yTail][xTail] = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xTail, yTail });
			cout << char(0);
			ok = FALSE;
			xTail--;
		}
	}; break;
	case 's':
	{
		if (posWalls[yTail+1][xTail] == 's')
		{
			posWalls[yTail][xTail] = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xTail, yTail });
			cout << char(0);
			ok = FALSE;
			yTail++;
		}
	}; break;
	case 'd':
	{
		if (posWalls[yTail][xTail +1] == 'd')
		{
			posWalls[yTail][xTail] = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xTail, yTail });
			cout << char(0);
			ok = FALSE;
			xTail++;
		}
	}; break;
	case 'w':
	{
		if (posWalls[yTail-1][xTail] == 'w')
		{
			posWalls[yTail][xTail] = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xTail, yTail });
			cout << char(0);
			ok = FALSE;
			yTail--;
		}
	}; break;
	}
	if (ok)
	{
		if (posWalls[yTail - 1][xTail] == 'w')
		{
			posWalls[yTail][xTail] = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xTail, yTail });
			cout << char(0);
			ok = FALSE;
			yTail--;
		}
		if (posWalls[yTail][xTail + 1] == 'd'&&ok)
		{
			posWalls[yTail][xTail] = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xTail, yTail });
			cout << char(0);
			ok = FALSE;
			xTail++;
		}
		if (posWalls[yTail][xTail - 1] == 'a'&&ok)
		{
			posWalls[yTail][xTail] = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xTail, yTail });
			cout << char(0);
			ok = FALSE;
			xTail--;
		}
		if (posWalls[yTail + 1][xTail] == 's'&&ok)
		{
			posWalls[yTail][xTail] = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xTail, yTail });
			cout << char(0);
			ok = FALSE;
			yTail++;
		}
	}
}

void gameOver()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { columns/2-7, rows/2-1 });
	cout << "Game over !";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { columns / 2 - 8, rows / 2 });
	cout << "Your score: " << Score;
}

void generateFood()
{
	int xRad = rand()%78+1;
	int yRad = rand()%23+1;
	if (posWalls[yRad][xRad] == 0)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xRad, yRad });
		cout << "M";
		posWalls[yRad][xRad] = 1;
	}
	else generateFood();
}

void generateBonus()
{
	int xRad = rand() % 78 + 1;
	int yRad = rand() % 23 + 1;
	if (posWalls[yRad][xRad] == 0)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xRad, yRad });
		cout << "B";
		posWalls[yRad][xRad] = 2;
	}
	else generateBonus();
}

void move(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xHead, yHead });
	cout << "0";
	xHead = xHead + x;
	yHead = yHead + y;
	switch (posWalls[yHead][xHead])
	{
	case 0: deleteTail(); break;
	case 1:{
		Score++;
		bonusTime++;
		generateFood();
		showScore();
	}; break;
	case 2:{
		Score += 2;
		bonusTime = 0;
		showScore();
	}; break;
	default:{ deleteTail(); notDead = 0; }
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { xHead, yHead });
	cout << "1";
	posWalls[yHead][xHead] = direction;
}

void update()
{
	while (notDead)
	{
		SYNCHRONIZE; if (bonusTime == 5){
			generateBonus();
			bonusTime++;
		}
		switch (direction)
		{
		case 'a':move(-1,0); break;
		case 's':move(0,1); break;
		case 'd':move(1,0); break;
		case 'w':move(0,-1); break;
		}
		changed = TRUE;
		Sleep(100);
	}
	gameOver();
}

void run()
{
	system("title Snake made by valecs97");
	getConsole();
	createSnake();
	generateFood();
	showScore();
	thread changeDir(changeDirection);
	thread startGame(update);
	startGame.join();
	changeDir.join();
}




int main()
{
	run();
	Sleep(1000);
}