//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war class: Prop(erty), it is a pure virtual class, derived as Plane, Tool, Bullet ;
#ifndef PROP_H
#define PROP_H
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <memory>
#include <math.h>
#include <string>

const double PI= 3.1415926535;

namespace prop {
	class Prop
	{
	public:

		Prop() = delete;
		Prop(const int& size, const double& velocity) 
			:size(size), velocity(velocity) {};
		

		virtual void Move(const int &control) = 0;
		void Advance();

		virtual void Shoot() = 0;

		virtual bool Interact( Prop&, const int &time) = 0;

		virtual const std::string Get_type()const = 0;

		bool Is_collide(const Prop&)const ;

		bool Is_destroyed(const int& time);

		const int Get_size() const {
			return size;
		} ;
		const COORD Get_position() const {
			return position;
		};
		const double Get_velocity() const
		{
			return velocity;
		};
		const double Get_dir()const {
			return theta;
		}

		void Set_direct(const double& d);

		void Set_velocity(const double& v);

		void Set_position(const COORD& posi);

		void Set_hitted(const int& time);

	private:
		const int size;
		COORD position = { 0.,0. };

		int hitted_time=0;
		int bomb_time_len=0;

		double velocity;
		double theta;
	};
}


#endif // !PROP_H
