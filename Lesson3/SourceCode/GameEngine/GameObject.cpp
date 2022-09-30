#include "GameObject.h"

void GameObject::SetTimer(GameTimer* timer)
{
	this->timer = timer;
}

void GameObject::SetPosition(float x, float y, float z)
{
	m_vPosition[0] = x;
	m_vPosition[1] = y;
	m_vPosition[2] = z;

	m_pRenderProxy->SetPosition(m_vPosition);
}

void GameObject::Move(float x, float y, float z)
{
	SetPosition(m_vPosition[0] + x, m_vPosition[1] + y, m_vPosition[2] + z);
}

void GameObject::Move(bx::Vec3 velocity)
{
	Move(velocity.x, velocity.y, velocity.z);
}
