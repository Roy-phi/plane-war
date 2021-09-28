//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is plane war core class: game, controlling the process of whole game;
#pragma once
#ifndef GAME_H
#define GAME_H
#include "Prop.h"
#include "Controller.h"
#include"Drawer.h"
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <tuple>
#include <memory>
#include <iostream>

namespace game {
	static int i = 0;
	using std::cout;
	using std::endl;
	class Game
	{
	public:

		Game() = delete;

		Game(const int& screen_H, const int& screen_W) 
			:game_controller(screen_H, screen_W), game_drawer(screen_H, screen_W){};
		
		~Game() {};
		
		Game(const Game &) = delete;       //Game don't need copy
		
		void Play();
		
	private:
		using Prop = std::shared_ptr<prop::Prop>;

		using prop_pool = std::unordered_map<prop_type,std::list<Prop>>;
										 //contian player plane, enemy plane, bullet, tool

		void Initial();					   //generate enviroment and initial parameter

		void Update();

		//void Set_control(const int&);

		void Game_over_check();           //check if game is over

		bool Collide_check();				//mark collided plane, and return whether player plane is hitted
										    //is -> true, no -> false
		void Generate_plane(); 

		void Move_prop();

		void Game_over();

		void Clean_battle_field();

		void Draw_battle_filed();

		void Clear();

		bool Is_move_out(const Prop &) const;
		

		prop_pool survival_pool;
		prop_pool bomb_pool;

		controller::Controller game_controller;

		drawer::Drawer game_drawer;

	};
}
#endif // !GAME_H


