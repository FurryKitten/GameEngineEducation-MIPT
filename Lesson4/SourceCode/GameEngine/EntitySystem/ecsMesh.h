#pragma once
#include "flecs.h"

struct CubeMesh {};
struct ProjectileMesh {};
struct RenderProxyPtr
{
	class RenderProxy* ptr;
	bool visible;
};

struct NotVisible {};

void register_ecs_mesh_systems(flecs::world &ecs);

