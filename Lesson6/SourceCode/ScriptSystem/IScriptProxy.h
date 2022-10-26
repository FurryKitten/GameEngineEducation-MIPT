#pragma once
#include "Common.h"
#include <any>

class SCRIPTSYSTEM_API IScriptProxy
{
public:
	virtual void Update() = 0;
};