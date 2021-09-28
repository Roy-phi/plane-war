//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war class: Plane
#pragma once
#ifndef PLANE_H
#define PLANE_H

#include <memory>
#include "Prop.h"

namespace plane {
	class Plane: public prop::Prop {
	public:
		Plane(const double &v, const double& theta, const COORD posi,const unsigned int & h_level,const std::string camp) 
			:Prop(v,theta,posi,camp),highest_level(h_level) {};
		virtual ~Plane() {};
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

