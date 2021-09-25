//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is plane war core class: game, controlling the process of whole game;
#include "game.h"
#include <Windows.h>
#include <conio.h>

namespace game {
	Game::Game() :time(0), state(1), player_control(0),is_game_over(false) {};
	Game::~Game() {};

	void Game::Initial() {
		time = 0;
		state = 1;
		player_control = 0;
		is_game_over = false;

		survival_pool = prop_pool(
			{
				{player_plane,std::list<Prop&>()},
				{enemy,std::list<Prop&>()},
				{bullet,std::list<Prop&>()},
				{tool,std::list<Prop&>()}
			}
		);

		stat = statistic(
			{
				{time_info,0},
				{beat_num,0},
				{state_level,1},
				{tool_num,0}
			});


		parameter = game_parameter(
			{
				{easy,{2,2,2.}},
				{medium,{3,1,3.}},
				{hard,{4,1,4}}
			});


	};

	void Game::Update() {
		Move_prop();

		is_game_over=Is_collide();

		Generate_plane();
	}

	void Game::Set_control(int& ct){
		player_control = ct;
	}

	void Game::Game_over_check()
	{
		if (is_game_over)
		{
			Game_over();

			///.... should be modified,if player want to continue
		}
	}

	void Game::Game_over()
	{
		//Draw();
	}

	bool Game::Is_collide() {
		for()
	}


}