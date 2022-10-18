
#include "ecsScripts.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "../ScriptSystem/ScriptSystem.h"

void register_ecs_script_systems(flecs::world& ecs)
{
	static auto inputQuery = ecs.query<InputHandlerPtr>();
	static auto scriptQuery = ecs.query<ScriptSystemPtr>();

	ecs.system<ScriptCreate>()
	  .each([&](flecs::entity e, ScriptCreate& script)
      {
        CScriptProxy* scriptProxy = nullptr;
        scriptQuery.each([&](ScriptSystemPtr scriptSystemPtr) {
          inputQuery.each([&](InputHandlerPtr& inputHandlePtr) {
            for (const auto& script : script.filenames)
            {
              scriptProxy = scriptSystemPtr.ptr->CreateProxy(script.c_str());
              initScript(scriptProxy, ecs, e, *inputHandlePtr.ptr);
            }
          });
        });
        //e.set(Script{ scriptProxy });
        e.remove<ScriptCreate>();
	  });
	
}


void initScript(CScriptProxy* scriptProxy, flecs::world& ecs, flecs::entity& e, InputHandler& inputHandler)
{

    sol::state& state = scriptProxy->getState();

    state.new_usertype<Velocity>("Velocity",
        "x", &Velocity::x,
        "y", &Velocity::y,
        "z", &Velocity::z);
    state.new_usertype<Position>("Position",
        "x", &Position::x,
        "y", &Position::y,
        "z", &Position::z);
    state.new_usertype<std::bitset<eIC_Max>>("Bitset",
        "test", &std::bitset<eIC_Max>::test);
    state.new_usertype<flecs::world>("World",
        "getEntity", [](flecs::world& self, flecs::entity_t id) { return self.entity(id); });
    state.new_usertype<InputHandler>("Input",
        "getState", &InputHandler::GetInputState);
    state.new_usertype<flecs::entity>("Entity",
        "getDeltaTime", [](flecs::entity self) { return self.delta_time(); },
        "getPosition", [](flecs::entity self) { return self.get<Position>(); },
        "setPosition", [](flecs::entity self, float x, float y, float z) { self.set<Position>({ x, y, z }); },
        "getVelocity", [](flecs::entity self) { return self.get<Velocity>(); },
        "setVelocity", [](flecs::entity self, float x, float y, float z) { self.set<Velocity>({ x, y, z }); });
    state.new_enum<EInputCommand>("Direction", {
        { "Left", EInputCommand::eIC_GoLeft },
        { "Right", EInputCommand::eIC_GoRight },
        { "Jump", EInputCommand::eIC_Jump }
        });

    state["entityId"] = e.id();
    state["world"] = std::ref(ecs);
    state["input"] = std::ref(inputHandler);


    //scriptProxy->SetVariable("entity", std::ref(e));

    /*scriptProxy->SetVariable("entityId", e.id());
    scriptProxy->SetVariable("world", std::ref(ecs));
    scriptProxy->SetVariable("input", std::ref(inputHandler));*/

    /*scriptProxy->SetVariable("Direction", 
    state.create_table_with(
        "Left", EInputCommand::eIC_GoLeft,
        "Right", EInputCommand::eIC_GoRight,
        "Jump", EInputCommand::eIC_Jump
    ));*/

    //sol::state& state = scriptProxy->getState();



    /*state["entity"] = e;
    state["input"] = inputHandler;
    state["Direction"] = state.create_table_with(
        "Left", EInputCommand::eIC_GoLeft,
        "Right", EInputCommand::eIC_GoRight,
        "Jump", EInputCommand::eIC_Jump
    );*/

}