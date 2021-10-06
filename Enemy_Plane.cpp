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
		std::normal_distribution<> dis(-0.1, 0.1);

		Prop::Set_direct(Prop::Get_dir()+dis(gen));

		Prop::Forward();

	}

	bool Enemy_Plane::Interact(Prop& anotherp, const int& time)
	{
		if (Prop::Is_collide(anotherp))
		{
			if (anotherp.Get_type() == "Tool")
			{
				anotherp.Set_hitted(time);//
				Upgrade();                //catch a tool, can improve level
				return true;
			}

			else if (anotherp.Get_type() == "Bullet" && !Plane::Is_same_camp(anotherp))
			{
				//if(bullet belong to Player)
				if (!anotherp.Is_hitted())
				{
					anotherp.Set_hitted(time);
					Degrade();
				}
				return true;
			}
		}
		return false;
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