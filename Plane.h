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
		Plane(const double &v, const double& theta, const COORD posi,const std::string camp,const int& W_limit, const int& H_limit,const unsigned int& h_level)
			:Prop(v,theta,posi,camp),highest_level(h_level),w_limit(W_limit),h_limit(H_limit) {};
		virtual ~Plane() {};
		void Upgrade();
		void Degrade();
		bool Is_same_camp(const Prop&)const;
		void Restrict_move_range(const int& size);
		virtual const int Get_level()const;

	private:
		unsigned int level = 1;  // player plane level range is 0-higest_level, if set to 0, game over,enemy also has level
		unsigned int highest_level;
		int w_limit;
		int h_limit;
	};
}

#endif // !PLANE_H

