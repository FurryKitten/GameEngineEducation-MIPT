#pragma once

#include <sol/sol.hpp>

#include "IScriptProxy.h"


class SCRIPTSYSTEM_API CScriptProxy final : public IScriptProxy
{
public:
	CScriptProxy(std::string filename);
	virtual void Update() override;
	sol::state& getState();
private:
	sol::load_result loadedScript;
	sol::state lua_script;
};

