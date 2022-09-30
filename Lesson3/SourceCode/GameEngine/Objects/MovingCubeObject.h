#pragma once

#include <bx/math.h>

#include "../GameObject.h"
#include "../RenderEngine/CubeRenderProxy.h"

class MovingCubeObject final : public GameObject
{
public:
	MovingCubeObject();
	void Update() override;

private:
	bx::Vec3 velocity;

};
