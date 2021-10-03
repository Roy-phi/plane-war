//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war class: Prop(erty), it is a pure virtual class, derived as Plane, Tool, Bullet ;

#include "Prop.h"

namespace prop {
	void Prop::Forward()
	{
		position.X += static_cast<int>(cos(theta) * velocity);
		position.Y += static_cast<int>(sin(theta) * velocity);
	}
	bool Prop::Is_collide(const Prop& other_p)const
	{
		const int other_size = other_p.Get_size();
		const COORD& other_posi = other_p.Get_position();

		return (position.Y - other_posi.Y  < other_size) && (other_posi.Y - position.Y < Get_size()) &&
			(position.X - other_posi.X  < other_size) && (other_posi.X - position.X   < Get_size());
			
	}
	bool Prop::Is_destroyed(const int& time)
	{
		return time - hitted_time > bomb_time_len;
	}
	void Prop::Set_hitted(const int& time)
	{
		hitted_time = time;
		is_hitted = true;
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