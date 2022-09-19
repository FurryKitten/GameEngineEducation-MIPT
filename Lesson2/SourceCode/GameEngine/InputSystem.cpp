#include "InputSystem.h"

InputSystem::InputSystem(std::string configFile) 
	: configReader(INIReader(configFile)),
	  kbl(GetKeyboardLayout(0))
{
	mapKey("w", 'W');
	mapKey("s", 'S');
	mapKey("a", 'A');
	mapKey("d", 'D');
	mapKey("left", VK_LEFT);
	mapKey("right", VK_RIGHT);
	mapKey("up", VK_UP);
	mapKey("down", VK_DOWN);

	mapAction(INPUT_ACTIONS::UP, configReader.Get("Keyboard", "Up", "w"));
	mapAction(INPUT_ACTIONS::DOWN, configReader.Get("Keyboard", "Down", "s"));
	mapAction(INPUT_ACTIONS::LEFT, configReader.Get("Keyboard", "Left", "a"));
	mapAction(INPUT_ACTIONS::RIGHT, configReader.Get("Keyboard", "Right", "d"));
}

bool InputSystem::actionKeyPressed(int actionCode)
{
	return GetAsyncKeyState(keyMap[actionMap[actionCode]]) & 0x8000;
}

void InputSystem::mapKey(std::string keyName, int keyCode)
{
	keyMap[keyName] = keyCode;
}

void InputSystem::mapAction(int actionCode, std::string keyCode)
{
	actionMap[actionCode] = keyCode;
}
