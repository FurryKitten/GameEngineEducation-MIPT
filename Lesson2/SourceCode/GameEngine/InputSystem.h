#pragma once

#include "Common.h"
#include "INIReader.h"

enum INPUT_ACTIONS
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


class InputSystem
{
public:
	InputSystem(std::string configFile);

	bool actionKeyPressed(int actionCode);
	void mapKey(std::string keyName, int keyCode);
	void mapAction(int actionCode, std::string keyName);
	
private:
	HKL kbl;
	INIReader configReader;
	std::map<std::string, int> keyMap;
	std::map<int, std::string> actionMap;
};