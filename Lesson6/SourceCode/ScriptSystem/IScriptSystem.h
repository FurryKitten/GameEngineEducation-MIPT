#pragma once
#include "Common.h"

class CScriptProxy;

class SCRIPTSYSTEM_API IScriptSystem
{
public:
	virtual void Update() = 0;
	virtual CScriptProxy* CreateProxy(const char* filename) = 0;
};
