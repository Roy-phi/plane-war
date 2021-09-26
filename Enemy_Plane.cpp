//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Enemy_Plane, it is derived from Plane;
#include"Enemy_Plane.h"


namespace enemy_plane {
	void Enemy_Plane::Move(const int &control)
	{
		std::default_random_engine random;
		std::uniform_real_distribution<double> v(0.0, 2 * Get_velocity());
		std::uniform_real_distribution<double> dir(0.0, Get_velocity());

		Prop::Set_direct(dir(random));
		Prop::Set_velocity(v(random));

		Prop::Forward();
		//maybe boundry check here;
	}
	void Enemy_Plane::Interact(Prop& anotherp, const int& time)
	{
		if (Prop::Is_collide(anotherp))
		{
			if (anotherp.Get_type() == "Tool")
			{
				anotherp.Set_hitted(time);//
				Upgrade();                //catch a tool, can improve level
			}

			else if (anotherp.Get_type() == "Bullet" && !Plane::Is_same_camp(anotherp))
			{
				//if(bullet belong to Player)
				anotherp.Set_hitted(time);
				Degrade();
			}
		}
	}

	const std::string Enemy_Plane::Get_type()const
	{
		return std::string("Enemy_Plane");
	}

	const int Enemy_Plane::Get_size()const
	{
		return static_cast<int>(shape.size());
	}

	const std::vector<int>& Enemy_Plane::Get_shape()const
	{
		return shape;
	}

	const std::shared_ptr<prop::Prop> Enemy_Plane::Shoot(const double& v) const
	{
		bullet::Bullet* eBullet = new bullet::Bullet(v, Prop::Get_dir(), Prop::Get_position(), "enemy");
														//set bullet parameter;
		std::shared_ptr<Prop> seBullet(eBullet);		//convert to shared_ptr(for safe)
																			
		return seBullet;    
	}
}