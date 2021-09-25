//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Player_Plane, it is derived from Plane;
#pragma once
#ifndef PLAYER_PLANE_H
#define PLAYER_PLANE_H
#include <vector>
#include "Plane.h"
extern const double PI;
namespace player_plane {
	class Player_Plane :public plane::Plane {
	public:
		virtual void  Move(const int &control) final override;

		virtual bool  Interact( Prop&,const int & time) final override;

		virtual const std::string Get_type()const final override;

	private:
		const double up = PI / 2;
		const double down = -PI / 2;
		const double left = PI;
		const double right = 0;

	};
}
#endif // !PLAYER_PLANE_H

