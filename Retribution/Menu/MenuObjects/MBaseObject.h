#pragma once
#include "../../SourceSDK/sdk.h"
#include <vector>

class MBaseObject
{
public:
	MBaseObject() { }
	virtual void Draw() = 0;
protected:
	bool active;
	int posX, posY;
	int sizeW, sizeH;
	int borderSize;
	std::string name;
	Color color{ 255, 255, 255, 255 };
	Color borderColorU{ 255, 255, 255, 255 };
	Color borderColorR{ 255, 255, 255, 255 };
	Color borderColorB{ 255, 255, 255, 255 };
	Color borderColorL{ 255, 255, 255, 255 };
};