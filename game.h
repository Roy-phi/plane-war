//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is plane war core class: game, controlling the process of whole game;
#pragma once
#ifndef GAME_H
#define GAME_H
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <tuple>
#include <memory>
#include "Prop.h"

class Prop;
class Drawer;
//class Floater;  //floating objects, such as bullet

namespace game {
	class Game
	{
	enum class hard_level{easy,medium,hard};
	enum class prop_type{player_plane,enemy,bullet,tool};
	enum class stat_info{time_info,beat_num,state_level,tool_num};
	enum class dir_type{down,left,up,right,down_left,left_up,up_right,right_down};

	public:
		Game() = delete;

		Game(const int &screen_H, const int &screen_W);
		
		~Game();
		
		Game(const Game &) = delete;       //Game don't need copy
		
		void Play();

	
	private:
		using Prop = std::shared_ptr<prop::Prop>;

		using prop_pool = std::unordered_map<prop_type,std::list<Prop>>;
										 //contian player plane, enemy plane, bullet, tool
		using statistic = std::unordered_map<stat_info, int>;
										//statistics info
		using game_parameter = std::unordered_map<hard_level, std::tuple<unsigned int, unsigned int, double>>;
								         //contain enemy nums, tool nums, bullet velocity
		using screen_posi = std::unordered_map<dir_type, COORD>;
										//contain positon on screen

		using test = std::unordered_map<hard_level, int>;

		void Initial();					   //generate enviroment and initial parameter

		void Update();

		void Set_control(const int&);

		void Game_over_check();           //check if game is over

		bool Collide_check();				//mark collided plane, and return whether player plane is hitted
										//is -> true, no -> false
		void Generate_plane(); 

		void Move_prop();

		void Game_over();

		void Destroyed_check();

		void Clear();
		

		prop_pool survival_pool;
		prop_pool bomb_pool;

		//
		int time=0;					//global time;
		unsigned int state;				//level 1, 2, 3
		int player_control;
		bool is_game_over;			//game over and excit
		bool excit;					//
		hard_level level;
		statistic stat;
		game_parameter parameter;
		screen_posi posi_set;

		const int screen_h;
		const int screen_w;				//window size

	};
}
#endif // !GAME_H


