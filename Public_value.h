
#pragma once
#ifndef PUBLICVALUE_H
#define PUBLICVALUE_H
#include <map>
#include <Windows.h>

// enum class
enum class prop_type { player_plane, enemy, bullet, tool };
enum class hard_level { easy, medium, hard ,extreme_hard};
enum class stat_info { time_info, beat_num, state_level, tool_num };
enum class posi_type { down, left, up, right, down_left, left_up, up_right, right_down };

// const value
const double PI = 3.1415926535;
const double up = PI / 2;
const double down = -PI / 2;
const double left = PI;
const double right = 0;

struct posi_set {
	posi_set(const int& screen_H, const int& screen_W)
		:screen_h(screen_H), screen_w(screen_W){
		p_set = std::map<posi_type, COORD>(
			{ 
			{ posi_type::down,        {static_cast<short>(screen_w *0.5),static_cast<short>(screen_h * 0.9)} },
			{ posi_type::left,        {static_cast<short>(screen_w *0.1),static_cast<short>(screen_h * 0.5)} },
			{ posi_type::up,          {static_cast<short>(screen_w *0.5),static_cast<short>(screen_h * 0.1)} },
			{ posi_type::right,       {static_cast<short>(screen_w *0.9),static_cast<short>(screen_h * 0.5)} },
			{ posi_type::down_left,   {static_cast<short>(screen_w *0.9),static_cast<short>(screen_h * 0.1)} },
			{ posi_type::left_up,     {static_cast<short>(screen_w *0.1),static_cast<short>(screen_h * 0.1)} },
			{ posi_type::up_right,    {static_cast<short>(screen_w *0.9),static_cast<short>(screen_h * 0.5)} },
			{ posi_type::right_down,  {static_cast<short>(screen_w *0.9),static_cast<short>(screen_h * 0.9)} }
			}
		);
	};

	const int screen_h;
	const int screen_w;


	const COORD original_point = { 0,0 };

	const COORD& operator[](const posi_type& type) const {
		auto it = p_set.find(type);
		if (it != p_set.end())
		{
			return it->second;
		}
		else
		{
			return original_point;
		}
	}

private:
	std::map<posi_type, COORD> p_set;

};

#endif // !PUBLICVALUE_H
