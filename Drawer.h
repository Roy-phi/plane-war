//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is plane war core class: Drawer, Draw the prop, control menu, and bomb dynamic process;

#pragma once
#ifndef DRAWER_H
#define DRAWER_H
#include "Controller.h"
#include "Prop.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

namespace drawer {
	using std::cout;
	using controller::Controller;

	class Drawer {
	public:
		

		Drawer(const int& screen_H, const int& screen_W) 
			:screen_h(screen_H), screen_w(screen_W) {
			Set_window_size(screen_h, screen_w);
		};

		void Draw_start_menu(Controller& game_controller);

		void Draw_select(Controller& game_controller);

		void Draw_prop(const prop::Prop& p);

		void Draw_bomb(const prop::Prop& p);

		void Draw_help();

		void Draw_static(const Controller& game_controller);

		void Draw_clear()const;
		void Draw_info(const int i);

	private:
		void Draw_point(const unsigned int& x, const unsigned int& y);
		void Draw_line(const unsigned int& x, const unsigned int& y, const  int len);
		void Set_window_size(const int& screen_H, const int& screen_W);

		void Set_cursor_position(const COORD& posi);
		void Set_cursor_position(const int & x,const int &y);

		void Set_color(const int &colorID);

		void Set_back_color();

		const int screen_h;
		const int screen_w;
	};
}

#endif // !DRAWER_H

