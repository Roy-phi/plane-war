#include<iostream>
#include<Windows.h>
#include<windows.h>
#include<conio.h>
#include"game.h"

int main()
{


	game::Game game(50,80);

	game.Play();

	system("pause");

	

	return 0;
}