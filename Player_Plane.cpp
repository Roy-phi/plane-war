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
			Prop::Set_direct(up);
			Prop::Forward();
			break;
		case 'd':
			Prop::Set_direct(right);
			Prop::Forward();
			break;
		case 'w':
			Prop::Set_direct(down);
			Prop::Forward();
			break;
		default:
			break;
		}  ///maybe can use map<char,vector<double>>
		Plane::Restrict_move_range(Get_size());
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
				if (!anotherp.Is_hitted())
				{
					anotherp.Set_hitted(time);
					Degrade();
				}
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
		COORD posi = Prop::Get_position();
		posi.X += Get_size() / 2-1;

		bullet::Bullet* eBullet = new bullet::Bullet(v, down, posi,Bullet_player_blue, "player");
														//set bullet parameter;
		std::shared_ptr<Prop> seBullet(eBullet);		//convert to shared_ptr(for safe)

		return seBullet;
	}
}