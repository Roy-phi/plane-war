//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Enemy_Plane, it is derived from Plane;
#include"Enemy_Plane.h"
#include <random>

namespace enemy_plane {
	void Enemy_Plane::Move(const int &control)
	{
		std::default_random_engine random;
		std::uniform_real_distribution<double> v(0.0, 2*Get_velocity());
		std::uniform_real_distribution<double> dir(0.0, Get_velocity());

		Prop::Set_direct({ vx(random),vy(random) });
		

	}
}