//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is plane war core class: game, controlling the process of whole game;
#include "game.h"
#include <Windows.h>
#include <conio.h>

namespace game {
	Game::Game() :time(0), state(1), player_control(0),
		is_game_over(false),level(hard_level::easy) {};

	Game::~Game() {};

	void Game::Initial() {
		time = 0;
		state = 1;
		player_control = 0;
		is_game_over = false;

		survival_pool = prop_pool(
			{
				{prop_type::player_plane,std::list<Prop>()},
				{prop_type::enemy,std::list<Prop>()},
				{prop_type::bullet,std::list<Prop>()},
				{prop_type::tool,std::list<Prop>()}
			}
		);

		stat = statistic(
			{
				{stat_info::time_info,0},
				{stat_info::beat_num,0},
				{stat_info::state_level,1},
				{stat_info::tool_num,0}
			});


		parameter = game_parameter(
			{
				{hard_level::easy,{2,2,2.}},
				{hard_level::medium,{3,1,3.}},
				{hard_level::hard,{4,1,4}}
			});


	};

	void Game::Update() {
		Move_prop();

		is_game_over=Collide_check();

		Generate_plane();
	}

	void Game::Set_control(const int& ct){
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

	bool Game::Collide_check() {
		//
		return false;
	}

	void Game::Generate_plane() {
		//
	}

	void Game::Move_prop() {
		//
	}

	void Game::Play() {
		Initial();
		
		while (1)
		{
			Sleep(10);       //pause 10ms;
			if (_kbhit())
			{
				Set_control(_getch());

				Update();

				break;

			}
		}
	}
}