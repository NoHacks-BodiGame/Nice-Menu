#include "Paint.h"

Paint gPaint;

void Paint::DrawLine(int _x1, int _y1, int _x2, int _y2, Color _color)
{
	gInterface.Surface()->DrawSetColor(_color.r(), _color.g(), _color.b(), _color.a());
	gInterface.Surface()->DrawLine(_x1, _y1, _x2, _y2);
}

void Paint::DrawFilledRect(int _x, int _y, int _width, int _height, Color _color)
{
	gInterface.Surface()->DrawSetColor(_color.r(), _color.g(), _color.b(), _color.a());
	gInterface.Surface()->DrawFilledRect(_x, _y, _x + _width, _y + _height);
}

void Paint::DrawFilledRectWithBorder(int _x, int _y, int _width, int _height, int _borderSize, Color _color, Color _borderColor)
{
	this->DrawFilledRect(_x - _borderSize, _y - _borderSize, _width + _borderSize * 2, _height + _borderSize * 2, _borderColor);
	this->DrawFilledRect(_x, _y, _width, _height, _color);
}

void Paint::DrawFilledRectWithBorder(int _x, int _y, int _width, int _height, int _borderSize, Color _color, Color _borderColorU, Color _bordercolorR, Color _borderColorB, Color _borderColorL)
{
	this->DrawFilledRect(_x, _y, _width, _height, _color);

	gPaint.DrawFilledRect(_x - _borderSize, _y - _borderSize, _width + _borderSize * 2, _borderSize, _borderColorU);
	gPaint.DrawFilledRect(_x + _width, _y, _borderSize, _height, _bordercolorR);
	gPaint.DrawFilledRect(_x - _borderSize, _y + _height, _width + _borderSize * 2, _borderSize, _borderColorB);
	gPaint.DrawFilledRect(_x - _borderSize, _y, _borderSize, _height, _borderColorL);
}

void Paint::DrawString(int _x, int _y, char _alignment, const std::string &_text, HFont _font, Color _color)
{
	std::wstring wStr = std::wstring(_text.begin(), _text.end());
	const wchar_t* wcStr = wStr.c_str();

	int textWidth = 0;
	int textHeight = 0;
	gInterface.Surface()->GetTextSize(_font, wcStr, textWidth, textHeight);

	switch (_alignment)
	{
	case 'c':
		_x -= textWidth / 2;
		break;
	case 'r':
		_x -= textWidth;
		break;
	case 'l':
		break;
	}

	_y -= textHeight / 2;

	gInterface.Surface()->DrawSetTextFont(_font);
	gInterface.Surface()->DrawSetTextColor(_color.r(), _color.g(), _color.b(), _color.a());
	gInterface.Surface()->DrawSetTextPos(_x, _y);
	gInterface.Surface()->DrawPrintText(wcStr, _text.size());
}

void Paint::DrawButton(int _x, int _y, int _width, int _height, const std::string &_text, HFont _font, Color _color, Color _textColor)
{
	this->DrawFilledRect(_x, _y, _width, _height, _color);
	this->DrawString(_x + _width / 2, _y + _height / 2, 'c', _text, _font, _textColor);
}

void Paint::DrawCursor(Color _color, Color _outlineColor)
{
	int cursorX = 0;
	int cursorY = 0;
	gInterface.Surface()->SurfaceGetCursorPos(cursorX, cursorY);
	
	// credits: D34dspy

	for (int i = 0; i <= 9; ++i)
		this->DrawLine(cursorX, cursorY, cursorX + i, cursorY + 11, _color);
	for (int i = 0; i <= 7; ++i)
		this->DrawLine(cursorX, cursorY + i + 9, cursorX + i, cursorY + 9, _color);
	for (int i = 0; i <= 3; ++i)
		this->DrawLine(cursorX + i + 6, cursorY + 11, cursorX, cursorY + i, _color);

	this->DrawLine(cursorX + 5, cursorY + 11, cursorX + 8, cursorY + 18, _color);
	this->DrawLine(cursorX + 4, cursorY + 11, cursorX + 7, cursorY + 18, _color);

	this->DrawLine(cursorX, cursorY, cursorX, cursorY + 17, _outlineColor);
	this->DrawLine(cursorX, cursorY + 17, cursorX + 3, cursorY + 14, _outlineColor);
	this->DrawLine(cursorX + 4, cursorY + 14, cursorX + 7, cursorY + 19, _outlineColor);
	this->DrawLine(cursorX + 5, cursorY + 14, cursorX + 7, cursorY + 19, _outlineColor);
	this->DrawLine(cursorX + 7, cursorY + 18, cursorX + 9, cursorY + 18, _outlineColor);
	this->DrawLine(cursorX + 10, cursorY + 18, cursorX + 7, cursorY + 12, _outlineColor);
	this->DrawLine(cursorX + 7, cursorY + 12, cursorX + 12, cursorY + 12, _outlineColor);
	this->DrawLine(cursorX + 12, cursorY + 12, cursorX, cursorY, _outlineColor);
}

HFont Paint::SetupFont(int _size, const std::string &_fontName, int _flags)
{
	HFont font = gInterface.Surface()->CreateFont();
	gInterface.Surface()->SetFontGlyphSet(font, _fontName.c_str(), _size, 0, 0, 0, _flags);
	
	return font;
}
