//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war class: Plane
#pragma once
#ifndef PLANE_H
#define PLANE_H

#include <memory>
#include "Prop.h"

extern const double PI;

namespace plane {
	class Plane: public prop::Prop {
	public:
		 const double up = PI / 2;
		 const double down = -PI / 2;
		 const double left = PI;
		 const double right = 0;

		Plane(const double &v, const double& theta, const COORD posi,const unsigned int & h_level,const std::string camp) 
			:Prop(v,theta,posi,camp),highest_level(h_level) {};
		void Upgrade();
		void Degrade();
		bool Is_same_camp(const Prop&)const;
		virtual const int Get_level()const;

	private:
		unsigned int level = 1;  // plane level range is 0-3, if set to 0, game over
		unsigned int highest_level;
	};
}

#endif // !PLANE_H

