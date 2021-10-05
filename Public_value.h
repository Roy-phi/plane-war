
#pragma once
#ifndef PUBLICVALUE_H
#define PUBLICVALUE_H
#include <map>
#include <Windows.h>

// enum class
enum class prop_type { player_plane, enemy, bullet, tool };
enum class hard_level { easy, medium, hard ,extreme_hard};
enum class stat_info { time_info, beat_num, state_level, tool_num };
enum class posi_type { down, down_left, right_down,left, up, right, left_up, up_right };

// const value
const double PI = 3.1415926535;
const double up = PI / 2;
const double down = -PI / 2;
const double left = PI;
const double right = 0;

//color
const int Player_plane_blue = FOREGROUND_BLUE;
const int Enemy_plane_green = FOREGROUND_GREEN;
const int Bullet_player_blue = FOREGROUND_BLUE;
const int Bullet_enemy_green = FOREGROUND_GREEN;
const int Tool_red = FOREGROUND_RED;
const int Other_color = FOREGROUND_GREEN;

const double low = 0.2;
const double high = 0.8;
const double middle = 0.5;

struct posi_set {
	posi_set(const int& screen_H, const int& screen_W)
		:screen_h(screen_H), screen_w(screen_W){
		p_set = std::map<posi_type, COORD>(
			{ 
			{ posi_type::down,        {static_cast<short>(screen_w *middle),static_cast<short>(screen_h * high)} },
			{ posi_type::down_left,   {static_cast<short>(screen_w * low),static_cast<short>(screen_h * high)} },
			{ posi_type::right_down,  {static_cast<short>(screen_w * high),static_cast<short>(screen_h * high)} },
			{ posi_type::left,        {static_cast<short>(screen_w *low),static_cast<short>(screen_h * middle)} },
			{ posi_type::up,          {static_cast<short>(screen_w *middle),static_cast<short>(screen_h * low)} },
			{ posi_type::right,       {static_cast<short>(screen_w *high),static_cast<short>(screen_h * middle)} },
			{ posi_type::left_up,     {static_cast<short>(screen_w *low),static_cast<short>(screen_h * low)} },
			{ posi_type::up_right,    {static_cast<short>(screen_w *high),static_cast<short>(screen_h * low)} }

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
