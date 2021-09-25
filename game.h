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

	public:
		Game();
		
		~Game();
		
		Game(const Game &) = delete;       //Game don't need copy
		
		void Play();

	
	private:
		using Prop = std::shared_ptr<prop::Prop>;

		using prop_pool = std::unordered_map<prop_type,std::list<Prop>>;
										 //contian player plane, enemy plane, bullet, tool
		using statistic = std::unordered_map<stat_info, int>;
										//statistics info
		using game_parameter = std::unordered_map<hard_level, std::tuple<int, int, double>>;
								         //contain enemy nums, tool nums, bullet velocity

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
		

		prop_pool survival_pool;
		prop_pool bomb_pool;

		//
		double time;					//global time;
		unsigned int state;				//level 1, 2, 3
		int player_control;
		bool is_game_over;
		hard_level level;
		statistic stat;
		game_parameter parameter;
		
	};
}
#endif // !GAME_H


