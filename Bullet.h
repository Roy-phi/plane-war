//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Bullet, it is derived from Prop;
#pragma once
#ifndef BULLET
#define BULLET
#include"Prop.h"
#include <string>

namespace bullet {
	class Bullet :public prop::Prop
	{
	public:
		Bullet(const double& v,const double &dir_theta,const COORD& posi,
			const std::string& camp)
			:Prop(v, dir_theta, posi,camp) {};

		virtual ~Bullet() {};
		
		virtual void Move(const int& control);

		virtual const std::string Get_type()const final override;

		virtual const std::vector<int>& Get_shape() const final override;

		virtual const int Get_size() const final override;

		virtual void  Interact(Prop&, const int& time)  final override {};

	private:
		const std::vector<int> shape_enemy = {1,1};
		const std::vector<int> shape_player = {1,1,1};
		const int level = 1;
	};
}
#endif // !BULLET

