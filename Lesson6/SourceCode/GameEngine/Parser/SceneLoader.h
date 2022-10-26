#pragma once

#include "tinyxml2.h"
#include <string>
#include <map>
#include <flecs.h>
#include <unordered_map>

enum ComponentTypes
{
	POSITION,
	VELOCITY,
	FRICTION,
	GRAVITY,
	BOUNCE_PLANE,
	BOUNCINESS,
	SCRIPTS,
	MESH
};


const static std::unordered_map <std::string, ComponentTypes> types
{
	{ "position", POSITION },
	{ "velocity", VELOCITY },
	{ "friction", FRICTION },
	{ "gravity", GRAVITY },
	{ "bouncePlane", BOUNCE_PLANE },
	{ "bounciness", BOUNCINESS },
	{ "scripts", SCRIPTS },
	{ "mesh", MESH }
};

class SceneLoader
{
public:

	SceneLoader(flecs::world& ecs, std::string filename);

	void registerEntities();

private:
	tinyxml2::XMLDocument doc;
	flecs::world& ecs;
	
	void setComponent(tinyxml2::XMLElement* el, flecs::entity& entity);

};