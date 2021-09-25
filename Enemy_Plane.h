//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Enemy_Plane, it is derived from Plane;
#pragma once
#ifndef ENEMY_PLANE_H
#define ENEMY_PLANE_H
#include "Plane.h"

namespace enemy_plane {
	class Enemy_Plane :public plane::Plane {
	public:
		virtual void  Move(const int& control) final override;

		virtual bool  Interact(Prop&, const int& time) final override;

		virtual const std::string Get_type()const final override;
	
	};
}

#endif // !ENEMY_PLANE_H

