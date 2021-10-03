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
		Tool(const double& v,
			const double& dir_theta, const COORD& posi, const std::string camp="neutral")
			:Prop(v, dir_theta, posi, camp) {};

		static const std::shared_ptr<prop::Prop> Generate(const double& v, const COORD& posi)
		{
			Tool* newTool = new Tool(v, PI / 2, posi); 
															   
			std::shared_ptr<Prop> pnewTool(newTool);		

			return pnewTool;
		}

		virtual ~Tool() {};

		virtual void Move(const int& control);

		virtual const std::string Get_type()const final override;

		virtual const std::vector<int>& Get_shape() const final override;

		virtual void  Interact(Prop&, const int& time)  final override {}

		virtual const int Get_size() const final override {
			return shape.size();
		} 
	private:
		const std::vector<int> shape = { 0,1,0 };
	};
}
#endif // !TOOL_H

