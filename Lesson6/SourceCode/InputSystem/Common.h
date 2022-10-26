#pragma once

#pragma warning(disable:4251)

#ifdef INPUTSYSTEM_EXPORTS
#define INPUTSYSTEM_API __declspec(dllexport)
#else
#define INPUTSYSTEM_API __declspec(dllimport)
#endif