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
#include "Tool.h"


namespace game {
	void Game::Initial() {

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

		game_controller.Initial();

		Generate_plane();  //generate essential plane

	};

	void Game::Clear()
	{
		survival_pool.clear();
		bomb_pool.clear();
	}

	void Game::Update() {
		Move_prop(); //move property

		if (Collide_check())          // prop Collide with each other, and return if player plane was hitted
		{
			game_controller.Set_game_over();
		}

		Game_over_check();  //check if game over and draw menu

		Clean_battle_field(); // after prop collided, destroy some props

		Draw_battle_field();  //draw new frame after clean battle field;

		Generate_plane();

	}

	void Game::Game_over_check()
	{
		if (game_controller.Is_game_over())
		{
			m_player.Game_over_sound();
			Game_over();         //draw game over info and select menu
		}
	}

	bool Game::Is_move_out(const Prop& p) const {

		//check if prop move out of screen, so easy

		const COORD& posi = (*p).Get_position();
		const int& size = (*p).Get_size();
		return posi.X < -size/2 || posi.Y < -size / 2 || (posi.X + size/2) > game_controller.Get_screen_w() || (posi.Y + size/2) > game_controller.Get_screen_h();
	}

	void Game::Clean_battle_field()
	{
		//bomb pool list
		auto& bomb_Enemy_Plane_List = bomb_pool[prop_type::enemy];
		auto& bomb_Bullet_List = bomb_pool[prop_type::bullet];

		//survival pool list
		auto& Enemy_Plane_List = survival_pool[prop_type::enemy];
		auto& Tool_List = survival_pool[prop_type::tool];
		auto& Bullet_List = survival_pool[prop_type::bullet];

		//check if plane hitted, add it to bomb list
		for (auto plane_it = Enemy_Plane_List.begin(); plane_it != Enemy_Plane_List.end();)
		{
			if ((*plane_it)->Get_level() <= 0)
			{
				bomb_Enemy_Plane_List.push_back(*plane_it);
				plane_it = Enemy_Plane_List.erase(plane_it);
			}
			else {
				++plane_it;
			}
		}

		//check if enemy plane move out, erase it from list
		for (auto plane_it = Enemy_Plane_List.begin(); plane_it != Enemy_Plane_List.end();)
		{
			if (Is_move_out(*plane_it))
			{
				plane_it = Enemy_Plane_List.erase(plane_it);
			}
			else {
				++plane_it;
			}
		}

		//check if bomb pool enemy plane destroyed, erase it;
		for (auto plane_it = bomb_Enemy_Plane_List.begin(); plane_it != bomb_Enemy_Plane_List.end();)
		{
			if ((*plane_it)->Is_destroyed(game_controller.Get_time()))
			{
				plane_it= bomb_Enemy_Plane_List.erase(plane_it);
			}
			else {
				++plane_it;
			}
		}

		//check if  pool bullet bomb, erase it and add to bomb list;
		for (auto bullet_it = Bullet_List.begin(); bullet_it != Bullet_List.end();)
		{
			if ((*bullet_it)->Is_hitted())
			{
				bomb_Bullet_List.push_back(*bullet_it);
				bullet_it = Bullet_List.erase(bullet_it);
			}
			else {
				++bullet_it;
			}
		}
		//check if bomb pool bullet destroyed, erase it;
		for (auto bullet_it = bomb_Bullet_List.begin(); bullet_it != bomb_Bullet_List.end();)
		{
			if ((*bullet_it)->Is_destroyed(game_controller.Get_time()))
			{
				bullet_it = bomb_Bullet_List.erase(bullet_it);
			}
			else {
				++bullet_it;
			}
		}

		//check if bullet move out of the screen, erase it;
		for (auto bullet_it = Bullet_List.begin(); bullet_it != Bullet_List.end();)
		{
			if (Is_move_out(*bullet_it))
			{
				bullet_it = Bullet_List.erase(bullet_it);
			}
			else {
				++bullet_it;
			}
		}

		//check if tool move out of the screen, erase it;
		//check if tool catched by plane, erase it;
		for (auto tool_it = Tool_List.begin(); tool_it != Tool_List.end();)
		{
			if (Is_move_out(*tool_it)|| (*tool_it)->Is_hitted())
			{
				tool_it = Tool_List.erase(tool_it);
			}
			else {
				++tool_it;
			}
		}
		
	}

	void Game::Draw_battle_field() {

		game_drawer.Draw_clear();

		//all survival prop in pool should be drew
		for (auto& survival_prop_list : survival_pool) {
			for (auto& survival_prop : survival_prop_list.second) {
				game_drawer.Draw_prop((*survival_prop)); // Draw_prop use Prop& as par,and survival_prop is share_ptr<Prop>
			}
		}

		//if bomb, use Draw_bomb()
		for (auto& bomb_prop_list : bomb_pool) {
			for (auto& bomb_prop : bomb_prop_list.second) {
				game_drawer.Draw_bomb((*bomb_prop));
			}
		}

		game_drawer.Draw_static(game_controller);
		game_drawer.Draw_info(i);

	}
	
	void Game::Game_over()
	{
		//Draw();
		game_drawer.Draw_game_over(game_controller);

		game_drawer.Draw_start_menu(game_controller);
		if (!game_controller.Is_excit())
		{
			Initial();
			game_drawer.Draw_select(game_controller);
		}

	}

	bool Game::Collide_check() {
		//player plane and enemy plane interact with enviroment(execute relevant method)
		//and check if player plane level is 0(means destroyed, game over,should return true)

		auto &Player_Plane_List = survival_pool[prop_type::player_plane];
		auto &Enemy_Plane_List = survival_pool[prop_type::enemy];
		auto &Tool_List = survival_pool[prop_type::tool];
		auto &Bullet_List = survival_pool[prop_type::bullet];

		//if bomb, add it to bomb list
		auto& bomb_Enemy_Plane_List = bomb_pool[prop_type::enemy];
		auto& bomb_Bullet_List = bomb_pool[prop_type::bullet];

		//player plane interact
		for (auto &player_plane : Player_Plane_List)
		{
			//shoot
			if (game_controller.Get_control() == 'k')
			{
				Bullet_List.push_back((dynamic_cast<plane::Plane*>( player_plane.get()) ->Shoot(game_controller.Get_bullet_vel())));
				m_player.Shoot_sound();
			}

			//interact with bullet
			for (auto &bullet : Bullet_List)
			{
				if (player_plane->Interact((*bullet), game_controller.Get_time())) {
					m_player.Hit_sound();
				};
			}
			//interact with enemy plane
			for (auto &e_plane : Enemy_Plane_List)
			{
				player_plane->Interact((*e_plane), game_controller.Get_time());
			}
			//interact with tool
			for (auto &tool : Tool_List)
			{
				if (player_plane->Interact((*tool), game_controller.Get_time())) {
					m_player.Upgrade();
				};
			}
			//if player plane level<=0,means destroyed,game over
			game_controller.Set_player_plane_level(player_plane->Get_level());
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
			if (game_controller.Shoot_or_not_e())
			{
				survival_pool[prop_type::bullet].push_back((dynamic_cast<plane::Plane*>(e_plane.get())->Shoot(game_controller.Get_bullet_vel())));
			}
			//interact with bullet
			for (auto& bullet : Bullet_List)
			{
				if (e_plane->Interact((*bullet), game_controller.Get_time())) {
					m_player.Hit_sound();
				};
			}
			//interact with tool
			for (auto& tool : Tool_List)
			{
				e_plane->Interact((*tool), game_controller.Get_time());
			}

			//if enemy plane level is 0(bomb), erase it from survival,add it to bomb list
			if (e_plane->Get_level() <= 0)
			{
				bomb_Enemy_Plane_List.push_back(e_plane);

				e_plane->Set_hitted(game_controller.Get_time());

				game_controller.Beat_enemy_add();

			}
		}
		return false;
	}

	void Game::Generate_plane() {
		//if pool(include survival pool and bomb pool) plane num decrease, fill up with it;
		while (survival_pool[prop_type::player_plane].size() < 1)
		{
			survival_pool[prop_type::player_plane].push_back(
				player_plane::Player_Plane::Generate(2, game_controller.screen_posi[posi_type::down],game_controller.Get_screen_w(),game_controller.Get_screen_h()));
		}
		while (survival_pool[prop_type::enemy].size() + bomb_pool[prop_type::enemy].size()+2
			<= game_controller.Get_enemy_num())
		{

			survival_pool[prop_type::enemy].push_back(
				enemy_plane::Enemy_Plane::Generate(game_controller.Get_enemy_plane_vel(), game_controller.Get_random_posi(), game_controller.Get_screen_w(), game_controller.Get_screen_h()));
		}

		if (game_controller.Is_generate_tool())
		{
			while (survival_pool[prop_type::tool].size() + bomb_pool[prop_type::tool].size()
				< game_controller.Get_tool_num())
			{

				survival_pool[prop_type::tool].push_back(
					tool::Tool::Generate(0.5, game_controller.Get_random_posi())); //random genarate tool
			}
		}

	}

	void Game::Move_prop() {
		//move every props in pool

		for (auto &list_pool : survival_pool)
		{
			for (auto& p : list_pool.second) //iterat in list(pair->second)
			{
				p->Move(game_controller.Get_control());      //control player plane,and will be ignored by others
			}
		}

	}

	void Game::Play() {

		Initial();

		game_drawer.Draw_start_menu(game_controller);
		if (!game_controller.Is_excit()) {
			game_drawer.Draw_select(game_controller);
			m_player.Backgound_sound(true);
		}
		
		while (!game_controller.Is_excit())
		{
			Sleep(game_controller.Get_frame_time());       //pause 10ms

			game_controller.Time_add();						//each frame time++

			if (_kbhit())
			{
				game_controller.Set_control(_getch());

				if (game_controller.Get_control() == 'q' || game_controller.Get_control() == 'Q')
				{
					game_controller.Excit();
				}
			}
			
			Update();
			game_controller.Set_control(0);
		}
		m_player.Backgound_sound(false);

		//std::cout << "game excit" << std::endl;
	}
}