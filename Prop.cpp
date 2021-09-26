//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war class: Prop(erty), it is a pure virtual class, derived as Plane, Tool, Bullet ;

#include "Prop.h"

namespace prop {
	void Prop::Forward()
	{
		position.X += static_cast<int>(sin(theta) * velocity);
		position.Y += static_cast<int>(cos(theta) * velocity);
	}
	bool Prop::Is_collide(const Prop& p)const
	{
		COORD pPosition = p.Get_position();
		int pSize = p.Get_size();
		return pow((pSize + Get_size()), 2) <=
			pow((pPosition.X) - position.X, 2) + pow((pPosition.Y) - position.Y, 2);
	}
	bool Prop::Is_destroyed(const int& time)
	{
		return time - hitted_time > bomb_time_len;
	}
	void Prop::Set_hitted(const int& time)
	{
		hitted_time = time;
	}
	void Prop::Set_position(const COORD& posi)
	{
		position = posi;
	};
	void Prop::Set_direct(const double& d)
	{
		theta = d;
	}
	void Prop::Set_velocity(const double& v)
	{
		velocity = v;
	}
}