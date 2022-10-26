#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "ecsScripts.h"
#include "tinyxml2.h"
#include "../Parser/SceneLoader.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, CScriptSystem* scriptSystem)
{


    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });
    ecs.entity("scriptSystem")
        .set(ScriptSystemPtr{ scriptSystem });

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);
    register_ecs_script_systems(ecs);

    SceneLoader sceneLoader(ecs, "../../../Assets/Scenes/Scene.xml");
    sceneLoader.registerEntities();
}

void EntitySystem::Update()
{
    ecs.progress();
}