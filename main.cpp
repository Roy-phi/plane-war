#include<iostream>
#include<Windows.h>
#include<conio.h>
#include"game.h"

int main()
{
	game::Game game;
	game.Initial();

		while (1)
		{
			Sleep(10);
			if (_kbhit())
			{
				player_control = _getch();

				Update();

				Draw();

			}

		}

	return 0;
}