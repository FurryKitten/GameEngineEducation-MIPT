#pragma once

#include "../GameObject.h"
#include "../RenderEngine/CubeRenderProxy.h"

class PhysicsCubeObject final : public GameObject
{
public:
	PhysicsCubeObject();
	void Update() override;

private:
	float gravity;
	bx::Vec3 velocity;
};
