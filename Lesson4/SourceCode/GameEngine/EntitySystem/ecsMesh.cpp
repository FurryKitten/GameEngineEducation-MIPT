#include "ecsMesh.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "RenderThread.h"
#include "RenderEngine.h"
#include "CubeRenderProxy.h"
#include "ecsControl.h"

void register_ecs_mesh_systems(flecs::world &ecs)
{
  static auto renderQuery = ecs.query<RenderEnginePtr>();
  ecs.system<const CubeMesh>()
    .each([&](flecs::entity e, const CubeMesh& cubeMesh)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
          RenderProxy* renderProxy = new CubeRenderProxy;
          re.ptr->GetRT()->EnqueueCommand(RC_CreateCubeRenderObject, renderProxy);

          float position[3];
          position[0] = 0.0f;
          position[1] = 0.0f;
          position[2] = 0.0f;

          renderProxy->SetPosition(position);

          e.set(RenderProxyPtr{ renderProxy, true });
          e.remove<CubeMesh>();
      });
    });

  
  ecs.system<const ProjectileMesh>()
    .each([&](flecs::entity e, const ProjectileMesh& projectileMesh)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
          RenderProxy* renderProxy = new CubeRenderProxy;
          re.ptr->GetRT()->EnqueueCommand(RC_CreateProjectileRenderObject, renderProxy);

          float position[3];
          position[0] = 0.0f;
          position[1] = 0.0f;
          position[2] = 0.0f;

          renderProxy->SetPosition(position);

          e.set(RenderProxyPtr{ renderProxy, true });
          e.remove<ProjectileMesh>();
      });
    });

  ecs.system<RenderProxyPtr, const Position>()
    .each([&](RenderProxyPtr &renderProxy, const Position &pos)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
           float position[3];
           position[0] = pos.x;
           position[1] = pos.y;
           position[2] = pos.z;

           renderProxy.ptr->SetPosition(position);
      });
    });

  
  ecs.system<NotVisible, RenderProxyPtr>()
    .each([&](flecs::entity e, NotVisible&, RenderProxyPtr& renderProxyPtr)
    {
      renderQuery.each([&](RenderEnginePtr re) {
          re.ptr->GetRT()->EnqueueCommand(RC_DeleteRenderObject, renderProxyPtr.ptr);
      });
      e.mut(e).clear();
      e.add<Projectile>();
    });
}

