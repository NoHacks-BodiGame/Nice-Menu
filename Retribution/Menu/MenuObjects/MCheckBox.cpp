#include "MCheckBox.h"

void MCheckBox::Init(int _posX, int _posY, int _size, int _borderSize, bool* _variable, const std::string &_name, HFont _font)
{
	this->posX = _posX;
	this->posY = _posY;
	this->sizeW = _size;
	this->sizeH = _size;
	this->borderSize = _borderSize;
	this->variable = _variable;
	this->name = _name;
	this->font = _font;
}

void MCheckBox::SetupColors(Color _color, Color _textColor, Color _nonActiveColor)
{
	this->color = _color;
	this->textColor = _textColor;
	this->nonActiveColor = _nonActiveColor;
}

void MCheckBox::Draw()
{
	if (!this->variable)
		return;
	
	if (gControls.OnClick(this->posX, this->posY, this->sizeW, this->sizeH))
		*this->variable = !*this->variable;
	
	if (*this->variable)
		gPaint.DrawFilledRect(this->posX, this->posY, this->sizeW, this->sizeH, this->color);
	else
		gPaint.DrawFilledRect(this->posX, this->posY, this->sizeW, this->sizeH, this->nonActiveColor);

	gPaint.DrawString(this->posX - this->sizeW, this->posY + this->sizeH / 2, 'r', this->name, this->font, this->textColor);
}