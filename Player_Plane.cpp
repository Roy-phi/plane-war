//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Player_Plane, it is derived from Plane;
#include "Player_Plane.h"

namespace player_plane {
	
	void Player_Plane::Move(const int &control)
	{
		switch (control)
		{
		case 'a':
			Prop::Set_direct(left);
			Prop::Forward();
			break;
		case 's':
			Prop::Set_direct(down);
			Prop::Forward();
			break;
		case 'd':
			Prop::Set_direct(right);
			Prop::Forward();
			break;
		case 'w':
			Prop::Set_direct(up);
			Prop::Forward();
			break;
		default:
			break;
		}  ///maybe can use map<char,vector<double>>
	}

	void Player_Plane::Interact( Prop & anotherp,const int &time) 
		//interact with enviroment, bullet,tool,and enemy plane
	{
		if (Prop::Is_collide(anotherp))
		{
			if (anotherp.Get_type() == "Tool")
			{
				anotherp.Set_hitted(time);//
				Upgrade();                //catch a tool, can improve level
			}

			else if (anotherp.Get_type() == "Bullet" && !Plane::Is_same_camp(anotherp))
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
	const int Player_Plane::Get_size()const
	{
		return static_cast<int>(shape.size());
	}

	const std::vector<int>& Player_Plane::Get_shape()const
	{
		return shape;
	}

	const std::shared_ptr<prop::Prop> Player_Plane::Shoot(const double& v) const
	{

		bullet::Bullet* eBullet = new bullet::Bullet(v, down, Prop::Get_position(), "player");
														//set bullet parameter;
		std::shared_ptr<Prop> seBullet(eBullet);		//convert to shared_ptr(for safe)

		return seBullet;
	}
}