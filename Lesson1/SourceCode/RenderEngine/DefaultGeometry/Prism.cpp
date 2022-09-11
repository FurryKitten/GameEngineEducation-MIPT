#include "Prism.h"
#include "../Shaders/ShadersHelper.h"

Prism::Prism()
{
	m_Layout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_prismVertices, sizeof(s_prismVertices))
		, m_Layout
	);

	// Create static index buffer for triangle list rendering.
	m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_prismTriList, sizeof(s_prismTriList))
	);

	m_ProgramHandle = ShadersHelper::LoadProgram("vs_cubes", "fs_cubes");
}