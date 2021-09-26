//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Bullet, it is derived from Prop;
#pragma once
#ifndef TOOL_H
#define TOOL_H
#include"Prop.h"
namespace tool {
	class Tool :public prop::Prop {
	public:
		Tool(const double& v, const std::string& identity,
			const double& dir_theta, const COORD& posi, const std::string camp="neutral")
			:Prop(v, dir_theta, posi, camp) {};

		virtual void Move(const int& control);

		virtual const std::string Get_type()const final override;

		virtual const std::vector<int>& Get_shape() const final override;

	private:
		const std::vector<int> shape = { 0,2,0 };
	};
}
#endif // !TOOL_H

