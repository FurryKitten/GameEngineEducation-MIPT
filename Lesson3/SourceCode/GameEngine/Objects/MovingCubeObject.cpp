#include "MovingCubeObject.h"

MovingCubeObject::MovingCubeObject() 
	: velocity{ bx::Vec3(bx::init::Zero) }
{
	m_pRenderProxy = new CubeRenderProxy();
}

void MovingCubeObject::Update()
{
	velocity = bx::Vec3(0.f, 0.f, sin(timer->TotalTime()) * timer->DeltaTime());
	Move(velocity);
}
