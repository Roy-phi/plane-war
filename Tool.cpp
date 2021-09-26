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
		//check boundry, if in boundry, set destroyed(out),else:
		Prop::Forward();
	}

	const std::string Tool::Get_type() const
	{
		return std::string("Tool");
	}
}