#pragma once
#include <memory>
#include "flecs.h"
#include "../../InputSystem/InputHandler.h"

class CScriptProxy;

struct ScriptCreate
{
	std::vector<std::string> filenames;
};

struct Script
{
	CScriptProxy* scriptProxy;
};

void register_ecs_script_systems(flecs::world& ecs);
void initScript(CScriptProxy* scriptProxy, flecs::world& ecs, flecs::entity& e, InputHandler& inputHandler);