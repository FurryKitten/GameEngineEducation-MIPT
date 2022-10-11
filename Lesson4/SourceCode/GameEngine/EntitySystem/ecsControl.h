#pragma once
#include "flecs.h"

struct Controllable {};
struct Enemy {};
struct JumpSpeed { float val; };

struct Projectile {};

struct Ammunition
{ 
	int maxBullets;
	int bulletCount;
	float time;
	float timeToReload;
	bool activeTimer;
};

void register_ecs_control_systems(flecs::world &ecs);

