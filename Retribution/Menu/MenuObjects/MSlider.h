#pragma once
#include "MBaseObject.h"

template<typename T>
class MSlider : public MBaseObject
{
public:
	MSlider() {}
	inline void Init(int _posX, int _posY, int _sizeW, int _sizeH, T* _variable, T _minValue, T _maxValue, int _precision, const std::string &_name, HFont _font)
	{
		this->posX = _posX;
		this->posY = _posY;
		this->sizeW = _sizeW;
		this->sizeH = _sizeH;
		this->variable = _variable;
		this->minValue = _minValue;
		this->maxValue = _maxValue;
		this->name = _name;
		this->precision = _precision;
		this->name = _name;
		this->font = _font;
	}
	inline void SetupColors(Color _color, Color _textColor, Color _nonActiveColor)
	{
		this->color = _color;
		this->textColor = _textColor;
		this->nonActiveColor = _nonActiveColor;
	}
	inline virtual void Draw() override
	{
		if (!this->variable)
			return;
		
		gPaint.DrawFilledRect(this->posX, this->posY, this->sizeW, this->sizeH, this->nonActiveColor);
		gPaint.DrawFilledRect(this->posX, this->posY, (int)(this->sizeW * (*this->variable - this->minValue) / (this->maxValue - this->minValue)), this->sizeH, this->color);

		if (gControls.DraggingSlider(this->posX, this->posY, this->sizeW, this->sizeH))
		{
			int cursorPosX;
			int cursorPosY;
			gInterface.Surface()->SurfaceGetCursorPos(cursorPosX, cursorPosY);

			float difference = (float)(cursorPosX - this->posX);
			float percent = difference / this->sizeW;
			float range = (this->maxValue - this->minValue) * percent;
			*this->variable = gUtils.ClampValue<T>(this->minValue + (T)range, this->minValue, this->maxValue);
		}

		gPaint.DrawString(this->posX - this->sizeH, this->posY + this->sizeH / 2, 'r', this->name, this->font, this->textColor);
		gPaint.DrawString(this->posX + this->sizeW + this->sizeH, this->posY + this->sizeH / 2, 'l', gUtils.ToStringWithPrecision(*variable, this->precision), this->font, this->textColor);
	}
private:
	T* variable;
	T minValue, maxValue;
	int precision;
	HFont font;
	Color textColor{ 255,255,255,100 };
	Color nonActiveColor{ 255,255,255,255 };
};