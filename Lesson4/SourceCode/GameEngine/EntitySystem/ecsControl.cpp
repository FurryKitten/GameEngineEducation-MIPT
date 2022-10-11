#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "../InputHandler.h"
#include "ecsMesh.h"

void register_ecs_control_systems(flecs::world &ecs)
{
  static bool isPressed = false;
  static auto inputQuery = ecs.query<InputHandlerPtr>();
  static auto projectileQuery = ecs.query<Projectile>();

  auto projPrefab = ecs.prefab("Projectile").set(Position{ 1.f, 0.f, 1.f })
      .set(Velocity{ 1.f, 0.f, 1.f })
      .set(Gravity{ 0.f, -9.8065f, 0.f })
      .set(BouncePlane{ 0.f, 1.f, 0.f, 5.f })
      .set(Bounciness{ 0.3f })
      .add<CubeMesh>()
      .add<Projectile>();

  ecs.system<Velocity, const Speed, const Controllable>()
    .each([&](flecs::entity e, Velocity &vel, const Speed &spd, const Controllable &)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        float deltaVelX = 0.f;
        float deltaVelZ = 0.f;
        if (input.ptr->GetInputState().test(eIC_GoLeft))
          deltaVelX -= spd;
        if (input.ptr->GetInputState().test(eIC_GoRight))
          deltaVelX += spd;
        if (input.ptr->GetInputState().test(eIC_GoDown))
          deltaVelZ -= spd;
        if (input.ptr->GetInputState().test(eIC_GoUp))
          deltaVelZ += spd;
        vel.x += deltaVelX * e.delta_time();
        vel.z += deltaVelZ * e.delta_time();
      });
    });
  
  ecs.system<const Position, Velocity, const Controllable, const BouncePlane, const JumpSpeed>()
    .each([&](const Position &pos, Velocity &vel, const Controllable &, const BouncePlane &plane, const JumpSpeed &jump)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane.x*pos.x + plane.y*pos.y + plane.z*pos.z < plane.w + planeEpsilon)
          if (input.ptr->GetInputState().test(eIC_Jump))
            vel.y = jump.val;
      });
    });

  ecs.system<Position, Controllable, Ammunition>()
    .each([&](flecs::entity e, Position &pos, Controllable &projectile, Ammunition &ammunition)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
          if (input.ptr->GetInputState().test(eIC_Shoot))
          {
            if (isPressed) return;
            bool isShooted = false;
            //projectileQuery.changed();
            projectileQuery.each([&](flecs::entity newProjectile, Projectile&) {
              if (!isShooted && ammunition.bulletCount > 0)
              {
                isShooted = true;
                ammunition.bulletCount -= 1;
                newProjectile.mut(e)
                .set(Position{pos.x, pos.y + 0.9f, pos.z})
                .set(Velocity{ 0.f, 0.f, 10.f })
                .set(Gravity{ 0.f, -9.8065f, 0.f })
                .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
                .set(Bounciness{ 0.6f })
                .set(BoxSize{ 0.1f, 0.1f, 0.1f })
                .set(Timer({ 0.f, 1.f, false }))
                .add<ProjectileMesh>()
                .remove<Projectile>();
              }
            });
            isPressed = true;
          }
          else
          {
              isPressed = false;
          }
      });
    });

    ecs.system<Controllable, Ammunition>()
    .each([&](flecs::entity e, Controllable &projectile, Ammunition &ammunition)
    {
      if (!ammunition.activeTimer && ammunition.bulletCount == 0)
      {
        ammunition.time = ammunition.timeToReload;
        ammunition.activeTimer = true;
      }
      if (ammunition.time > 0.f)
      {
        ammunition.time -= e.delta_time();
      }
      if (ammunition.activeTimer && ammunition.time <= 0.f)
      {
        ammunition.bulletCount = ammunition.maxBullets;
        ammunition.activeTimer = false;
      }
    });

  ecs.system<Timer>()
    .each([&](flecs::entity e, Timer &timer)
    {
      if (timer.time > 0.f)
      {
        timer.time -= e.delta_time();
      }
      if (timer.active && timer.time <= 0.f)
      {
          e.mut(e)
           .add<NotVisible>();
      }
    });

}

