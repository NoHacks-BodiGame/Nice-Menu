#pragma once
#include <string>
#include "..\Definitions\Definitions.h"
#include "..\Misc\Color.h"
#include "..\Interfaces\Interfaces.h"
#include "..\Interfaces\Surface.h"

class Paint
{
public:
	void DrawLine(int _x1, int _y1, int _x2, int _y2, Color _color);
	void DrawFilledRect(int _x, int _y, int _width, int _height, Color _color);
	void DrawFilledRectWithBorder(int _x, int _y, int _width, int _height, int _borderSize, Color _color, Color _borderColor);
	void DrawFilledRectWithBorder(int _x, int _y, int _width, int _height, int _borderSize, Color _color, Color _borderColorU, Color _bordercolorR, Color _borderColorB, Color _borderColorL);
	void DrawString(int _x, int _y, char _alignment, const std::string &_text, HFont _font, Color _color);
	void DrawButton(int _x, int _y, int _width, int _height, const std::string &_text, HFont _font, Color _color, Color _textColor);
	void DrawCursor(Color _color, Color _outlineColor);
	HFont SetupFont(int _size, const std::string &_fontName, int _flags = FONTFLAG_ANTIALIAS);
};

extern Paint gPaint;