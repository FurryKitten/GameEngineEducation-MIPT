// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "Objects/ControllableCubeGameObject.h"
#include "Objects/PhysicsCubeObject.h"
#include "Objects/MovingCubeObject.h"
#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "InputHandler.h"

int randomInt(int from, int to)
{
    return from + rand() % (to - from + 1);
}

GameObject* createRandomCube(RenderThread* renderThread, GameTimer* timer, InputHandler* inputHandler)
{
    int objType = randomInt(0, 2);
    GameObject* newObj = NULL;
    switch (objType) 
    {
    case 0:
        newObj = new PhysicsCubeObject();
        break;
    case 1:
        newObj = new MovingCubeObject();
        break;
    case 2:
        newObj = new ControllableCubeGameObject(*inputHandler);
        break;
    }
    newObj->SetTimer(timer);
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, newObj->GetRenderProxy());
    return newObj;
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

    srand(time(NULL));

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();
    InputHandler* inputHandler = new InputHandler();


    GameObject* randomObjects[100];
    for (int i = 0; i < 100; ++i)
    {
        randomObjects[i] = createRandomCube(renderThread, &timer, inputHandler);
        randomObjects[i]->SetPosition((i % 10) * 2.f, 0.0f, (i / 10) * 2.f);
    }

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    float newPositionX = 0.0f;

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
            inputHandler->Update();

            timer.Tick();

            for (const auto& obj : randomObjects)
            {
                obj->Update();
            }

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
