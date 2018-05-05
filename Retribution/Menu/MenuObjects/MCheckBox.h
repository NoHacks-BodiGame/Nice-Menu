#pragma once
#include "MBaseObject.h"

class MCheckBox : public MBaseObject
{
public:
	void Init(int _posX, int _posY, int _size, int _borderSize, bool* _variable, const std::string &_name, HFont _font);
	void SetupColors(Color _color, Color _textColor, Color _nonActiveColor);
	virtual void Draw() override;
private:
	HFont font;
	Color textColor{ 255,255,255,100 };
	Color nonActiveColor{ 255,255,255,255 };
	bool* variable;
};