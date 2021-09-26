//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Player_Plane, it is derived from Plane;
#pragma once
#ifndef PLAYER_PLANE_H
#define PLAYER_PLANE_H
#include <array>
#include "Plane.h"
#include "Bullet.h"

class Bullet;
namespace player_plane {
	class Player_Plane :public plane::Plane {
	public:
		Player_Plane(const double& v, const double& theta, const COORD posi, 
			const unsigned int& h_level = 3,const std::string camp="player")
			:Plane(v, theta, posi,h_level,camp) {};
		
		static const std::shared_ptr<prop::Prop> Generate(const double& v, const COORD& posi)
		{
			Player_Plane* newPlane = new Player_Plane(v, PI / 2, posi); //default level=2,camp=player 
															   //set player plane parameter;
			std::shared_ptr<Prop> pnewPlane(newPlane);		//convert to shared_ptr(for safe)

			return pnewPlane;
		}
		virtual void  Move(const int &control) final override;

		virtual void  Interact( Prop&,const int & time) final override;

		virtual const std::string Get_type()const final override;

		virtual const int Get_size() const final override;

		virtual const std::vector<int>& Get_shape() const final override;

		virtual const std::shared_ptr<prop::Prop> Shoot(const double& v)const final override;

	private:


		const std::vector<int> shape = { 1,1,4,4,1,1,1,3 }; //const shape
	};
}
#endif // !PLAYER_PLANE_H

