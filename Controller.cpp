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
				{hard_level::easy,{2,2,1.5,0.3}},
				{hard_level::medium,{3,1,1.5,0.3}},
				{hard_level::hard,{4,1,2.,0.5}},
				{hard_level::extreme_hard, {5,1,2.5,1.0}}
			});
	}
	void Controller::Improve_difficulty() {
		std::get<0>(parameter[level]) += 1;
		std::get<2>(parameter[level]) += 0.5;
		std::get<3>(parameter[level]) += 0.2;
		++state;
	}

	COORD Controller::Get_random_posi() {
		std::random_device rd;  // Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<double> dis(3., 8.);
		return screen_posi[static_cast<posi_type>(static_cast<int>(dis(gen)))];
		//return screen_posi[posi_type::up_right];
	}
}

