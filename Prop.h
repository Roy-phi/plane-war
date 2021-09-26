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
#include <array>

const double PI= 3.1415926535;
class Bullet;
namespace prop {
	class Prop
	{
	public:

		Prop(const double& velocity,const double& theta,const COORD posi,const std::string camp) 
			:velocity(velocity), theta(theta), position(posi),camp(camp) {};
		
		virtual void Move(const int &control) = 0;
		void Forward();

		virtual const std::shared_ptr<Prop> Shoot(const double& v)const { return std::shared_ptr<Prop>(); };

		virtual void Interact( Prop&, const int &time) = 0;

		virtual const std::string Get_type()const = 0;

		virtual const std::vector<int>& Get_shape() const = 0;

		virtual const int Get_level() const { return 0; };

		bool Is_collide(const Prop&)const ;

		bool Is_destroyed(const int& time);

		virtual const int Get_size() const = 0;

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

		const std::string& Get_camp() const {
			return camp;
		}

		void Set_direct(const double& d);

		void Set_velocity(const double& v);

		void Set_position(const COORD& posi);

		void Set_hitted(const int& time);

	private:
		COORD position ;

		const std::string camp;

		int hitted_time=-1;
		int bomb_time_len=0;

		double velocity;
		double theta;
	};
}


#endif // !PROP_H
