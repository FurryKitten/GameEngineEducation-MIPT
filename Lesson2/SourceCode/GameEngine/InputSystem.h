#pragma once

#include "Common.h"
#include "INIReader.h"

enum INPUTS
{
	UP = 'W',
	DOWN = 'S',
	LEFT = 'A',
	RIGHT = 'D'
};

class InputSystem
{
public:
	InputSystem(std::string configFile);

	bool keyPressed(int keycode);

private:
	HKL kbl;
	INIReader configReader;
};