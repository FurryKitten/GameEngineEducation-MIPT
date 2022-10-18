#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "../../ScriptSystem/ScriptSystem.h"
#include "../../InputSystem/InputHandler.h"

class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, CScriptSystem* scriptSystem);

	void Update();
private:
	flecs::world ecs;
};

