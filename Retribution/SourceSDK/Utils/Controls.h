#pragma once
#include "..\Definitions\Definitions.h"
#include "..\Interfaces\Interfaces.h"
#include "..\Interfaces\Surface.h"
#include "..\Interfaces\InputSystem.h"

class Interface;

class Controls
{
public:
	bool Hover(int _targetPosX, int _targetPosY, int _boundsW, int _boundsH);
	bool Toggle(ButtonCode_t _code);
	bool OnClick(int _targetPosX, int _targetPosY, int _boundsW, int _boundsH);
	bool DraggingSlider(int _targetPosX, int _targetPosY, int _boundsW, int _boundsH);
private:
	bool InBounds(int _posX, int _posY, int _targetPosX, int _targetPosY, int _boundsW, int _boundsH);
private:
	bool keyStates[256];
	int firstPressPosX;
	int firstPressPosY;
};

extern Controls gControls;