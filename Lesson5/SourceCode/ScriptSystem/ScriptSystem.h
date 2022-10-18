#pragma once

#include "IScriptSystem.h"
#include "ScriptProxy.h"

class SCRIPTSYSTEM_API CScriptSystem final : public IScriptSystem {
public:
	CScriptSystem();

	virtual void Update() override;
	virtual CScriptProxy* CreateProxy(const char* filename) override;

private:
	std::vector<CScriptProxy*> scriptProxies;
};