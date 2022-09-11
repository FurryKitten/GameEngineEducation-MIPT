#pragma once

#include "../RenderObject.h"

class Prism : public RenderObject
{
public:
	Prism();

private:
	inline static const PosColorVertex s_prismVertices[] =
	{
		{ 0.0f,		 1.0f,  2.0f, 0xffff0000 },  // 0
		{ 0.86603f, -0.5f,  2.0f, 0xff00ff00 },  // 1
		{-0.86603f, -0.5f,  2.0f, 0xff0000ff },  // 2
		{ 0.0f,		 1.0f, -2.0f, 0xffffff00 },  // 3
		{ 0.86603f, -0.5f, -2.0f, 0xff00ffff },  // 4
		{-0.86603f, -0.5f, -2.0f, 0xffff00ff }   // 5
	};

	inline static const uint16_t s_prismTriList[] =
	{
		0, 1, 2, // 0
		3, 5, 4, // 1
		1, 4, 2, // 2
		2, 4, 5, // 3
		0, 2, 5, // 4
		0, 5, 3, // 5
		0, 3, 1, // 6
		1, 3, 4  // 7
	};
};

