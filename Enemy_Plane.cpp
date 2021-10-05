//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is a plane war key class: Enemy_Plane, it is derived from Plane;
#include"Enemy_Plane.h"


namespace enemy_plane {
	void Enemy_Plane::Move(const int &control)
	{
		//std::default_random_engine random;
		std::random_device rd;  // Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
		std::normal_distribution<> dis(-0.3, 0.3);
		//std::uniform_real_distribution<double> v(0.0,  1.5*Get_velocity());
		//std::uniform_real_distribution<double> dir(0.0, 2*PI);

		
		Prop::Set_direct(Prop::Get_dir()+dis(gen));

		Prop::Forward();

		//Plane::Restrict_move_range(Get_size());

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
				if (!anotherp.Is_hitted())
				{
					anotherp.Set_hitted(time);
					Degrade();
				}
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
		COORD posi = Prop::Get_position();
		posi.X += Get_size()/2-1;

		bullet::Bullet* eBullet = new bullet::Bullet(v, up , posi,Bullet_enemy_green, "enemy");
														//set bullet parameter;
		std::shared_ptr<Prop> seBullet(eBullet);		//convert to shared_ptr(for safe)
																			
		return seBullet;    
	}
}