#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "ecsScripts.h"
#include "tinyxml2.h"
#include "../Parser/SceneLoader.h"

template <typename T, typename... Args>
void setAttributes(flecs::world& ecs, T component, Args... args)
{
    auto entity = ecs.entity().set(T{ args... });
}

void registerEntities(flecs::world& ecs, std::string filename)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filename.c_str());
    //doc.Parse();
    auto entitiesXml = doc.FirstChildElement("entities");
    auto entityXml = entitiesXml->FirstChildElement("entity");
    while (entityXml != NULL)
    {
        auto positionEl = entityXml->FirstChildElement("transform");
        auto physicsEl = entityXml->FirstChildElement("physics");
        std::string pos = positionEl->Attribute("position");
        std::string gravity = physicsEl->Attribute("gravity");
        std::string friction = physicsEl->Attribute("friction");
        std::string bouncePlane = physicsEl->Attribute("bouncePlane");
        std::string bounciness = physicsEl->Attribute("bounciness");

        std::stringstream ss(pos);
        float val;
        while (ss >> val)
        {
           // vect.push_back(i);
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }

        entityXml->NextSiblingElement("entity");
    }

}

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

    //auto cubeControl = ecs.entity()
    //    .set(Position{ 0.f, 0.f, 0.f })
    //    .set(Velocity{ 0.f, 0.f, 0.f })
    //    .set(FrictionAmount{ 0.9f })
    //    .set(Gravity{ 0.f, -9.8065f, 0.f })
    //    .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
    //    .set(Bounciness{ 0.3f })
    //    //.add<Controllable>()
    //    .set(ScriptCreate{ std::vector<std::string>{
    //    "../../../Assets/scripts/jumpable.lua",
    //    "../../../Assets/scripts/movable.lua"} })
    //    .add<CubeMesh>();

    //auto cubeMoving = ecs.entity()
    //    .set(Position{ 0.f, 0.f, 0.f })
    //    .set(Velocity{ 0.f, 3.f, 0.f })
    //    .set(Gravity{ 0.f, -9.8065f, 0.f })
    //    .set(BouncePlane{ 0.f, 1.f, 0.f, 5.f })
    //    .set(Bounciness{ 1.f })
    //    .add<CubeMesh>();
}

void EntitySystem::Update()
{
    ecs.progress();
}