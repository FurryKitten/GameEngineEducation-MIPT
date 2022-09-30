#pragma once

#include <bx/math.h>

#include "Common.h"
#include "RenderProxy.h"
#include "GameTimer.h"

inline bx::Vec3 operator*(const bx::Vec3& vec, const float& x)
{
	return bx::Vec3(vec.x * x, vec.y * x, vec.z * x);
}

class GameObject
{
public:
	GameObject() = default;

	~GameObject()
	{
		delete m_pRenderProxy;
	}

	void SetTimer(GameTimer* timer);

	void SetPosition(float x, float y, float z);
	void Move(float x, float y, float z);
	void Move(bx::Vec3 velocity);

	virtual void Update() = 0;

	RenderProxy* const GetRenderProxy() { return m_pRenderProxy; }
protected:
	RenderProxy* m_pRenderProxy;

	GameTimer *timer;
	float m_vPosition[3];
};

