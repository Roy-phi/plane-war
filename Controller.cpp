//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is plane war core class: Controller, controlling the info of whole game;
#include "Controller.h"

namespace controller {
	void Controller::Initial() {
		time = 0;					//global time;
		state = 0;				//level 1, 2, 3
		player_control = 0;
		is_game_over = false;			//game over 
		excit = false;					//tag if excit

		level = hard_level::easy;

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
				{hard_level::hard,{4,1,4}},
				{hard_level::extreme_hard, {6,1,5}}
			});
	}
}