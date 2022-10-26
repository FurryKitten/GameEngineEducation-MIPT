#include "ScriptProxy.h"
#include "../../../SDKs/flecs/src/flecs.h"
#include "../GameEngine/EntitySystem/ecsSystems.h"
#include "../InputSystem/InputHandler.h"
#include "../GameEngine/EntitySystem/ecsPhys.h"

void registerUsertypes(sol::state& state)
{
    state.new_usertype<Velocity>("Velocity",
        "x", &Velocity::x,
        "y", &Velocity::y,
        "z", &Velocity::z);
    state.new_usertype<flecs::world>("World",
        "getEntity", [](flecs::world& self, flecs::entity_t id) { return self.entity(id); });
    state.new_usertype<InputHandler>("Input",
        "getState", &InputHandler::GetInputState);
    state.new_usertype<flecs::entity>("Entity",
        "getDeltaTime", [](flecs::entity self) { return self.delta_time(); },
        "getPosition", [](flecs::entity& self) { self.get<Position>(); },
        "setPosition", [](flecs::entity& self, float x, float y, float z) { self.set<Position>({ x, y, z }); },
        "getVelocity", [](flecs::entity self) { return self.get<Velocity>(); },
        "setVelocity", [](flecs::entity self, float x, float y, float z) { self.set<Velocity>({ x, y, z }); });
    state.new_enum<EInputCommand>("Direction", {
        { "Left", EInputCommand::eIC_GoLeft },
        { "Right", EInputCommand::eIC_GoRight },
        { "Jump", EInputCommand::eIC_Jump }
    });

}

CScriptProxy::CScriptProxy(std::string filename)
{
	lua_script.open_libraries(sol::lib::base);
	loadedScript = lua_script.load_file(filename);
}

void CScriptProxy::Update()
{
    auto res = loadedScript();
}

sol::state& CScriptProxy::getState()
{
    return lua_script;
}