#include "ControllableCubeGameObject.h"
#include "../RenderEngine/CubeRenderProxy.h"

ControllableCubeGameObject::ControllableCubeGameObject(InputHandler& inputHandler)
	: velocity{bx::init::Zero},
	inputHandler{inputHandler}
{
	m_pRenderProxy = new CubeRenderProxy();
}

void ControllableCubeGameObject::Update()
{
	velocity = bx::Vec3(0.0f, 0.0f, 0.0f);
	if (inputHandler.GetInputState().test(eIC_GoLeft))
	{
		velocity = bx::Vec3(-3.0f, 0.0f, 0.0f);
	}
	if (inputHandler.GetInputState().test(eIC_GoRight))
	{
		velocity = bx::Vec3(3.0f, 0.0f, 0.0f);
	}
	Move(velocity * timer->DeltaTime());
}
