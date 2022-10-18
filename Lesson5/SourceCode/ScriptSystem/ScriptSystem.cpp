#include "ScriptSystem.h"


CScriptSystem::CScriptSystem()
{
    return;
}

void CScriptSystem::Update()
{
    for (const auto& proxy : scriptProxies)
    {
        proxy->Update();
    }
}

CScriptProxy* CScriptSystem::CreateProxy(const char* filename)
{
    CScriptProxy* newProxy = new CScriptProxy(filename);
    scriptProxies.push_back(newProxy);
    return newProxy;
}
