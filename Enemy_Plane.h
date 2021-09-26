//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Enemy_Plane, it is derived from Plane;
#pragma once
#ifndef ENEMY_PLANE_H
#define ENEMY_PLANE_H
#include "Plane.h"
#include "Bullet.h"
#include <random>

namespace enemy_plane {
	class Enemy_Plane :public plane::Plane {
	public:
		Enemy_Plane(const double& v, const double& theta, const COORD& posi, 
			const unsigned int& h_level = 2,const std::string camp="enemy")
			:Plane(v, theta, posi, h_level,camp) {};

		static const std::shared_ptr<prop::Prop> Generate(const double& v, const COORD& posi)
		{
			Enemy_Plane* newPlane = new Enemy_Plane(v, -PI/2, posi); //default level=2,camp=enemy 
			                                                   //set enemy plane parameter;
			std::shared_ptr<Prop> pnewPlane(newPlane);		//convert to shared_ptr(for safe)

			return pnewPlane;
		}

		virtual void  Move(const int& control) final override;

		virtual void  Interact(Prop&, const int& time) final override;

		virtual const std::string Get_type()const final override;

		virtual const int Get_size() const final override;

		virtual const std::vector<int>& Get_shape() const final override;

		virtual const std::shared_ptr<prop::Prop> Shoot(const double& v)const final override;

	private:

		const std::vector<int> shape = { 2,1,2,2,1,1}; //const shape
	};
}

#endif // !ENEMY_PLANE_H

