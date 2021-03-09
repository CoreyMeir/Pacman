#pragma once
// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"
#include "Structure.h"
#include <string>
// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;
class Pacman : public Game
{
private:
	SoundEffect* _pop;
public:
};