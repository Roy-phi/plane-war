//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is plane war core class: game, controlling the process of whole game;
#include "game.h"
#include "Enemy_Plane.h"
#include "Player_Plane.h"
#include <Windows.h>
#include <conio.h>
#include "Prop.h"


namespace game {
	Game::Game(const int& screen_H, const int& screen_W) :time(0), state(1), player_control(0),
		is_game_over(false),level(hard_level::easy),screen_h(screen_H),screen_w(screen_W),excit(false) {};

	Game::~Game() {};



	void Game::Initial() {
		time = 0;
		state = 1;
		player_control = 0;
		is_game_over = false;

		Clear();  //clear survival pool and bomb pool

		survival_pool = prop_pool(
			{
				{prop_type::player_plane,std::list<Prop>()},
				{prop_type::enemy,std::list<Prop>()},
				{prop_type::bullet,std::list<Prop>()},
				{prop_type::tool,std::list<Prop>()}
			}
		);

		bomb_pool = prop_pool(
			{
				{prop_type::player_plane,std::list<Prop>()},
				{prop_type::enemy,std::list<Prop>()},
				{prop_type::bullet,std::list<Prop>()},
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

		Generate_plane();  //generate essential plane

	};

	void Game::Clear()
	{
		survival_pool.clear();
		bomb_pool.clear();
	}

	void Game::Update() {
		Move_prop();

		is_game_over=Collide_check();

		Game_over_check();

		Destroyed_check();

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
			//Draw() start page
		}
	}

	void Game::Destroyed_check()
	{
		//bomb pool list
		auto& bomb_Enemy_Plane_List = bomb_pool[prop_type::enemy];
		auto& bomb_Bullet_List = bomb_pool[prop_type::bullet];

		//survival pool list
		auto& Tool_List = survival_pool[prop_type::tool];
		auto& Bullet_List = survival_pool[prop_type::bullet];

		//check if bomb pool enemy plane destroyed, erase it;
		for (auto plane_it = bomb_Enemy_Plane_List.begin(); plane_it != bomb_Enemy_Plane_List.end();)
		{
			if ((*plane_it)->Is_destroyed(time))
			{
				plane_it= bomb_Enemy_Plane_List.erase(plane_it);
			}
			else {
				++plane_it;
			}
		}

		//check if bomb pool bullet destroyed, erase it;
		for (auto bullet_it = bomb_Bullet_List.begin(); bullet_it != bomb_Bullet_List.end();)
		{
			if ((*bullet_it)->Is_destroyed(time))
			{
				bullet_it = bomb_Bullet_List.erase(bullet_it);
			}
			else {
				++bullet_it;
			}
		}

		//check if bullet move out of the screen, erase it;
		for (auto bomb_bullet_it = bomb_Bullet_List.begin(); bomb_bullet_it != bomb_Bullet_List.end();)
		{
			if ((*bomb_bullet_it)->Is_destroyed(time))
			{
				bomb_bullet_it = bomb_Bullet_List.erase(bomb_bullet_it);
			}
			else {
				++bomb_bullet_it;
			}
		}

		//check if tool move out of the screen, erase it;
		for (auto tool_it = Tool_List.begin(); tool_it != Tool_List.end();)
		{
			if ((*tool_it)->Is_move_out(screen_h, screen_w))
			{
				tool_it = Tool_List.erase(tool_it);
			}
			else {
				++tool_it;
			}
		}

		

	}

	void Game::Game_over()
	{
		//Draw();
	}

	bool Game::Collide_check() {
		//player plane and enemy plane interact with enviroment(execute relevant method)
		//and check if player plane level is 0(means destroyed, game over,should return true)

		auto &Player_Plane_List = survival_pool[prop_type::player_plane];
		auto &Enemy_Plane_List = survival_pool[prop_type::enemy];
		auto &Tool_List = survival_pool[prop_type::tool];
		auto &Bullet_List = survival_pool[prop_type::bullet];

		//player plane interact
		for (auto &player_plane : Player_Plane_List)
		{
			//shoot
			if (player_control == 'k' && time % 20 == 0)
			{
				Bullet_List.push_back(player_plane->Shoot(1));
			}

			//interact with bullet
			for (auto &bullet : Bullet_List)
			{
				player_plane->Interact((*bullet),time);
			}
			//interact with enemy plane
			for (auto &e_plane : Enemy_Plane_List)
			{
				player_plane->Interact((*e_plane), time);
			}
			//interact with tool
			for (auto &tool : Tool_List)
			{
				player_plane->Interact((*tool), time);
			}
			//if player plane level<=0,means destroyed,game over
			if (player_plane->Get_level() <= 0)
			{
				return true;
			}
		}

		//enemy plane interact
		for (auto& e_plane : Enemy_Plane_List)
		{
			//cause player plane interacted with enemy plane before, so ignore here;
			//shoot
			if (time % 30 == 0)
			{
				Bullet_List.push_back(e_plane->Shoot(1));
			}
			//interact with bullet
			for (auto& bullet : Bullet_List)
			{
				e_plane->Interact((*bullet), time);
			}
			//interact with tool
			for (auto& tool : Tool_List)
			{
				e_plane->Interact((*tool), time);
			}
		}
		return false;
	}

	void Game::Generate_plane() {
		//if pool(include survival pool and bomb pool) plane num decrease, fill up with it;
		while (survival_pool[prop_type::player_plane].size() < 1)
		{
			survival_pool[prop_type::player_plane].push_back(
				player_plane::Player_Plane::Generate(1, posi_set[dir_type::down]));
		}
		while (survival_pool[prop_type::enemy].size() + bomb_pool[prop_type::enemy].size()
			< std::get<0>(parameter[level]))
		{
			survival_pool[prop_type::enemy].push_back(
				enemy_plane::Enemy_Plane::Generate(1, posi_set[dir_type::up]));
		}
	}

	void Game::Move_prop() {
		//move every props in pool
		for (auto &list_pool : survival_pool)
		{
			for (auto& p : list_pool.second) //iterat in list(pair->second)
			{
				p->Move(player_control);      //control player plane,and will be ignored by others
			}
		}

	}

	void Game::Play() {
		Initial();
		
		while (!excit)
		{
			Sleep(10);       //pause 10ms;
			if (_kbhit())
			{
				Set_control(_getch());

				Update();

				if (player_control == 'q' || player_control == 'Q')
				{
					excit = true;
				}
			}
		}
	}
}