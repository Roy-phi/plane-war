//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Plane, it is derived from Prop;

#include "Plane.h"

namespace plane {
	void Plane::Upgrade()
	{
		if (level <highest_level && level>0) // once set as 0, game over, can't upgrade
		{
			level += 1;
		}
	}
	void Plane::Degrade()
	{
		if (level > 0)
		{
			level -= 1;
		}
	}
	bool Plane::Is_same_camp(const Prop& p)const
	{
		return p.Get_camp() == Get_camp();
	}

	const int Plane::Get_level()const
	{
		return level;
	}

}