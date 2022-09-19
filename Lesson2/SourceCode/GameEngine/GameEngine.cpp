// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <bx/math.h>

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
#include "InputSystem.h"
#include "INIReader.h"

void getInputVelocity(InputSystem& inputSystem, bx::Vec3& vel)
{
    vel = { 0.f, 0.f, 0.f };
    if (inputSystem.actionKeyPressed(INPUT_ACTIONS::UP))
    {
        vel.y = 1.f;
    }
    if (inputSystem.actionKeyPressed(INPUT_ACTIONS::DOWN))
    {
        vel.y = -1.f;
    }
    if (inputSystem.actionKeyPressed(INPUT_ACTIONS::LEFT))
    {
        vel.x = -1.f;
    }
    if (inputSystem.actionKeyPressed(INPUT_ACTIONS::RIGHT))
    {
        vel.x = 1.f;
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    InputSystem inputSystem("input_config.ini");
    bx::Vec3 cubePosition(bx::init::Zero);
    bx::Vec3 cubeVelocity(bx::init::Zero);

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();

    GameObject* cube = new CubeGameObject();
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            float t = 0;
            timer.Tick();
            
            //t = sin(timer.TotalTime())*2;
            
            getInputVelocity(inputSystem, cubeVelocity);
            cubePosition = bx::add(cubePosition, bx::mul(cubeVelocity, 0.01f));
            cube->SetPosition(cubePosition.x, 0.0f, cubePosition.y);
           
            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
