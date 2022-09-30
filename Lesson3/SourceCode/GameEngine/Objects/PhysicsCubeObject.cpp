#include "PhysicsCubeObject.h"


PhysicsCubeObject::PhysicsCubeObject()
	: velocity{ bx::init::Zero },
	gravity{ 9.81f }
{
	m_pRenderProxy = new CubeRenderProxy();
}

void PhysicsCubeObject::Update()
{
	if (m_vPosition[1] <= 0.0f)
	{
		velocity = bx::Vec3(0.f, gravity, 0.f);
	}
	else
	{
		velocity = bx::Vec3(0.f, (velocity.y - gravity * timer->DeltaTime()), 0.f);
	}
	Move(velocity * timer->DeltaTime());
}
