//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Bullet, it is derived from Prop;

#include"Bullet.h"

namespace bullet {
	const std::vector<int>& Bullet::Get_shape() const
	{
		if (Get_camp() == "enemy")
		{
			return shape_enemy;
		}
		else
		{
			return shape_player;
		}
	}
	void Bullet::Move(const int& control)//ignore control;
	{
		//check boundry, if in boundry, set destroyed(out),else:
		Prop::Forward();
	}

	const std::string Bullet::Get_type()const
	{
		return std::string("Bullet");
	}

	const int Bullet::Get_size()const
	{
		if (Get_camp() == "enemy")
		{
			return static_cast<int>(shape_enemy.size());
		}
		else
		{
			return static_cast<int>(shape_player.size());
		}
	}
}