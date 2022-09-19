#include "InputSystem.h"

InputSystem::InputSystem(std::string configFile) 
	: configReader(INIReader(configFile)),
	  kbl(GetKeyboardLayout(0))
{
}

bool InputSystem::keyPressed(int keycode)
{
	return GetAsyncKeyState(keycode) & 0x8000;
}
