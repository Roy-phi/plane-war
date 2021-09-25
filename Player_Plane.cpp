//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Player_Plane, it is derived from Plane;
#include "Player_Plane.h"
#include "Prop.cpp"

namespace player_plane {
	
	void Player_Plane::Move(const int &control)
	{

		switch (control)
		{
		case 'a':
			Prop::Set_direct(left);
			Prop::Advance();
			break;
		case 's':
			Prop::Set_direct(down);
			Prop::Advance();
			break;
		case 'd':
			Prop::Set_direct(right);
			Prop::Advance();
			break;
		case 'w':
			Prop::Set_direct(up);
			Prop::Advance();
			break;
		default:
			break;
		}  ///maybe can use map<char,vector<double>>
		
	}

	bool Player_Plane::Interact( Prop & anotherp,const int &time) 
		//interact with enviroment, bullet,tool,and enemy plane
	{
		if (Prop::Is_collide(anotherp))
		{
			if (anotherp.Get_type() == "Tool")
			{
				anotherp.Set_hitted(time);//
				Upgrade();                //catch a tool, can improve level
			}

			else if (anotherp.Get_type() == "Bullet")
			{
				anotherp.Set_hitted(time);
				Degrade();
			}
			else if(anotherp.Get_type() == "Enemy_Plane")
			{
				anotherp.Set_hitted(time);
				Degrade();
			}
		}
	}
	const std::string Player_Plane::Get_type()const
	{
		return std::string("Player_Plane");
	}
}