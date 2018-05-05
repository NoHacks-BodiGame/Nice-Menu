#include "Controls.h"

Controls gControls;

bool Controls::InBounds(int _posX, int _posY, int _targetPosX, int _targetPosY, int _boundsW, int _boundsH)
{
	return (_posX > _targetPosX && _posY > _targetPosY &&
		_posX < _targetPosX + _boundsW && _posY < _targetPosY + _boundsH);
}

bool Controls::Hover(int _targetPosX, int _targetPosY, int _boundsW, int _boundsH)
{
	int cursorPosX = 0;
	int cursorPosY = 0;
	gInterface.Surface()->SurfaceGetCursorPos(cursorPosX, cursorPosY);

	return this->InBounds(cursorPosX, cursorPosY, _targetPosX, _targetPosY, _boundsW, _boundsH);
}

bool Controls::Toggle(ButtonCode_t _code)
{
	bool result = false;
	
	if (gInterface.InputSystem()->IsButtonDown(_code))
	{
		if (!this->keyStates[_code])
		{
			result = true;
			this->keyStates[_code] = true;
		}
	}
	else
		this->keyStates[_code] = false;

	return result;
}

bool Controls::OnClick(int _targetPosX, int _targetPosY, int _boundsW, int _boundsH)
{
	bool result = false;

	static int firstPressPosX = 0;
	static int firstPressPosY = 0;
	
	static unsigned long long lastButtonPressedTick = 0;

	static bool buttonIsDown = false;

	if (gInterface.InputSystem()->IsButtonDown(MOUSE_LEFT))
	{
		if (!buttonIsDown)
		{
			gInterface.Surface()->SurfaceGetCursorPos(firstPressPosX, firstPressPosY);
			buttonIsDown = true;
		}
		
		lastButtonPressedTick = GetTickCount64();
	}
	else
	{
		if (buttonIsDown)
		{
			if (this->InBounds(firstPressPosX, firstPressPosY, _targetPosX, _targetPosY, _boundsW, _boundsH) &&
				this->Hover(_targetPosX, _targetPosY, _boundsW, _boundsH))
			{
				result = true;
				buttonIsDown = false;
			}

			if (GetTickCount64() - lastButtonPressedTick > 20)
				buttonIsDown = false;
		}
	}
	
	return result;
}

bool Controls::DraggingSlider(int _targetPosX, int _targetPosY, int _boundsW, int _boundsH)
{
	bool result = false;

	static int firstPressPosX = 0;
	static int firstPressPosY = 0;
	
	static bool buttonIsDown = false;

	if (gInterface.InputSystem()->IsButtonDown(MOUSE_LEFT))
	{
		if (!buttonIsDown)
		{
			gInterface.Surface()->SurfaceGetCursorPos(firstPressPosX, firstPressPosY);
			buttonIsDown = true;
		}

		if (this->InBounds(firstPressPosX, firstPressPosY, _targetPosX, _targetPosY, _boundsW, _boundsH))
			result = true;
	}
	else
		buttonIsDown = false;
		
	return result;
}