#include<iostream>
#include<Windows.h>
#include<windows.h>
#include<conio.h>
#include"game.h"
void SetConsoleWindowSize(SHORT width, SHORT height)
{
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT wrt = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(hStdOutput, TRUE, &wrt); // ���ô���ߴ�
	COORD coord = { width, height };
	SetConsoleScreenBufferSize(hStdOutput, coord); // ���û���ߴ�
}

int main()
{
	game::Game game(100,100);
	SetConsoleWindowSize(200, 200);
	game.Play();
	system("pause");

	return 0;
}