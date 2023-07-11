//badger
#pragma once

#include "./image.h"
#include "./obj.h"

using namespace std;

struct player:public obj{
	float jump_force=1000;
	uint8_t hit=0;

	player(float jump_force2,obj& obj2):jump_force(jump_force2),obj(obj2){}
};