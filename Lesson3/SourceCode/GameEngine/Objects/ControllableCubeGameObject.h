#pragma once

#include "../GameObject.h"
#include "../InputHandler.h"

class ControllableCubeGameObject final : public GameObject
{
public:
	ControllableCubeGameObject(InputHandler& inputHandler);
	void Update() override;

private:
	InputHandler& inputHandler;
	bx::Vec3 velocity;
};

