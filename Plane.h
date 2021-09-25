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
		void Upgrade();
		void Degrade();
	private:
		unsigned int level = 1;  // plane level range is 0-3, if set to 0, game over
	};
}

#endif // !PLANE_H

