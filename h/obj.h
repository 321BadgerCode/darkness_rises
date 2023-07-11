//badger
#pragma once

#include "./const.h"
#include "./image.h"

using namespace std;

struct obj:public image{
	int health=100;
	int damage=10;
	int speed=100;
	int mass=10;
	int weight;

	obj(int health2,int damage2,int speed2,int mass2,image& image2):health(health2),damage(damage2),speed(speed2),mass(mass2),image(image2){
		weight=mass*(int)gravity;
	}
};