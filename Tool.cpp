//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Tool, it is derived from Prop;

#include"Tool.h"

namespace tool {
	const std::vector<int>& Tool::Get_shape() const
	{
		return shape;
	}
	void Tool::Move(const int& control)//ignore control;
	{
		std::random_device rd;  // Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
		std::normal_distribution<> dis(0, 1.0);

		Prop::Set_direct(Prop::Get_dir() + dis(gen));

		Prop::Forward();
	}

	const std::string Tool::Get_type() const
	{
		return std::string("Tool");
	}
}