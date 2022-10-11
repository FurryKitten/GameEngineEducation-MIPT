#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);

    auto cubeControl = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 0.f, 0.f })
        .set(Speed{ 10.f })
        .set(FrictionAmount{ 0.9f })
        .set(JumpSpeed{ 10.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
        .set(Bounciness{ 0.3f })
        .set(Ammunition{ 3, 3, 0.0f, 1.0f, false })
        .add<Controllable>()
        .add<CubeMesh>();
    
    for (int i = -2; i <= 2; ++i)
    {
        ecs.entity()
            .set(Position{ i * 2.2f - 2.f, 0.f, 4.f })
            .set(Velocity{ 0.f, 3.f, 0.f })
            .set(Gravity{ 0.f, -9.8065f, 0.f })
            .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
            .set(Bounciness{ 0.9f })
            .set(BoxSize{ 1.f, 1.f, 1.f })
            .add<Enemy>()
            .add<CubeMesh>();
    }
 
    for (int i = 0; i < 100; ++i)
    {
        ecs.entity()
            .add<Projectile>();
    }
}

void EntitySystem::Update()
{
    ecs.progress();
}