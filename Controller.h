//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is plane war core class: Controller, controlling the info of whole game;
#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Public_value.h"
#include <unordered_map>



namespace controller {
	class Controller {
		//
	public:
		//contain positon on screen
		using test = std::unordered_map<hard_level, int>;
		
		using statistic = std::unordered_map<stat_info, int>;
		//statistics info

		using game_parameter = std::unordered_map<hard_level, std::tuple<unsigned int, unsigned int, double>>;
		//contain enemy nums, tool nums, bullet velocity

		Controller(const int& screen_H, const int& screen_W) 
			:screen_h(screen_H), screen_w(screen_W),screen_posi(screen_H,screen_W) {};

		void Initial();

		//Set function
		void Set_control(const int& ctr) {player_control = ctr;}

		void Excit() { excit = true; }

		void Set_hard_level(const hard_level& lev) { level = lev; }

		void Time_add() { ++time; };

		void Set_game_over() { is_game_over = true; };

		void Beat_enemy_add() { ++(stat[stat_info::beat_num]); };
		void Catch_tool_add() { ++(stat[stat_info::tool_num]); };

		//Get function
		const bool Is_excit()const { return excit; };

		const int Get_control()const { return player_control; };

		const int Get_time() const { return time; };

		const unsigned int Get_state() const {return state;};

		const bool Is_game_over() const {return is_game_over;};

		const hard_level Get_hard_level() const { return level; };
	
		const int Get_beat_num()const  { 
			auto it = stat.find(stat_info::beat_num);
			if (it != stat.end()) {
				return  it->second;
			}
			else {
				return -1;
			}
		};

		const int Get_catch_tool_num()const {
			auto it = stat.find(stat_info::tool_num);
			if (it != stat.end()) {
				return  it->second;
			}
			else {
				return -1;
			}
		};
		
		const int Get_screen_h()const { return screen_h; };

		const int Get_screen_w()const { return screen_w; };

		const unsigned int Get_tool_num() { return std::get<1>(parameter[level]); };

		const unsigned int Get_enemy_num() { return std::get<0>(parameter[level]); };

		const double Get_bullet_vel(){ return std::get<2>(parameter[level]); }

		posi_set screen_posi;          //position set, 8 direct

	private:
		int time = 0;					//global time;
		unsigned int state = 0;				//level 1, 2, 3
		int player_control = 0;
		bool is_game_over = false;			//game over 
		bool excit = false;					//tag if excit

		hard_level level = hard_level::easy;

		statistic stat;

		game_parameter parameter;

		const int screen_h;
		const int screen_w;				//window size
	};
}

#endif // !CONTROLLER_H
