#include "ecsPhys.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include <stdlib.h>

static float rand_flt(float from, float to)
{
  return from + (float(rand()) / RAND_MAX) * (to - from);
}

static bool aabbIntersect(Position p1, BoxSize b1, Position p2, BoxSize b2)
{
    return p1.x >= p2.x - b2.x
        && p1.x <= p2.x + b2.x
        && p1.y >= p2.y - b2.y
        && p1.y <= p2.y + b2.y
        && p1.z >= p2.z - b2.z
        && p1.z <= p2.z + b2.z;
}

void register_ecs_phys_systems(flecs::world &ecs)
{
  
  static auto timerQuery = ecs.query<Timer>();
  static auto bulletQuery = ecs.query<Position, BoxSize, Timer>();
  static auto ammunitionQuery = ecs.query<Ammunition>();

  ecs.system<Velocity, const Gravity, BouncePlane*, Position*>()
    .each([&](flecs::entity e, Velocity &vel, const Gravity &grav, BouncePlane *plane, Position *pos)
    {
      if (plane && pos)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane->x * pos->x + plane->y * pos->y + plane->z * pos->z < plane->w + planeEpsilon)
          return;
      }
      vel.x += grav.x * e.delta_time();
      vel.y += grav.y * e.delta_time();
      vel.z += grav.z * e.delta_time();
    });


  ecs.system<Velocity, Position, const BouncePlane, const Bounciness>()
    .each([&](Velocity &vel, Position &pos, const BouncePlane &plane, const Bounciness &bounciness)
    {
      float dotPos = plane.x * pos.x + plane.y * pos.y + plane.z * pos.z;
      float dotVel = plane.x * vel.x + plane.y * vel.y + plane.z * vel.z;
      if (dotPos < plane.w)
      {
        pos.x -= (dotPos - plane.w) * plane.x;
        pos.y -= (dotPos - plane.w) * plane.y;
        pos.z -= (dotPos - plane.w) * plane.z;

        vel.x -= (1.f + bounciness.val) * plane.x * dotVel;
        vel.y -= (1.f + bounciness.val) * plane.y * dotVel;
        vel.z -= (1.f + bounciness.val) * plane.z * dotVel;
      }
    });

  ecs.system<Position, BoxSize, Enemy>()
    .each([&](flecs::entity e, Position &pos, BoxSize &boxSize, Enemy&)
    {
      bulletQuery.each([&](flecs::entity bullet, Position& bulletPos, BoxSize &bulletBoxSize, Timer &) {
        if (aabbIntersect(bulletPos, bulletBoxSize, pos, boxSize))
        {
          bullet.mut(e)
           .add<NotVisible>();
          e.mut(e)
           .add<NotVisible>();
          ammunitionQuery.each([&](Ammunition &ammunition){
            ++ammunition.maxBullets;
          });
        }
      });
    });

  ecs.system<Velocity, Timer, const Gravity, BouncePlane*, Position*>()
    .each([&](flecs::entity e, Velocity &vel, Timer& timer, const Gravity &grav, BouncePlane *plane, Position *pos)
    {
      if (plane && pos)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane->x * pos->x + plane->y * pos->y + plane->z * pos->z < plane->w + planeEpsilon)
          timerQuery.each([&](flecs::entity e, Timer& timer) {
            if (!timer.active)
            {
              timer.time = timer.timeToAction;
              timer.active = true;
            }
          });
          return;
      }
    });

  ecs.system<Velocity, const FrictionAmount>()
    .each([&](flecs::entity e, Velocity &vel, const FrictionAmount &friction)
    {
      vel.x -= vel.x * friction.val * e.delta_time();
      vel.y -= vel.y * friction.val * e.delta_time();
      vel.z -= vel.z * friction.val * e.delta_time();
    });


  ecs.system<Position, const Velocity>()
    .each([&](flecs::entity e, Position &pos, const Velocity &vel)
    {
      pos.x += vel.x * e.delta_time();
      pos.y += vel.y * e.delta_time();
      pos.z += vel.z * e.delta_time();
    });


  ecs.system<Position, const ShiverAmount>()
    .each([&](flecs::entity e, Position &pos, const ShiverAmount &shiver)
    {
      pos.x += rand_flt(-shiver.val, shiver.val);
      pos.y += rand_flt(-shiver.val, shiver.val);
      pos.z += rand_flt(-shiver.val, shiver.val);
    });
}

