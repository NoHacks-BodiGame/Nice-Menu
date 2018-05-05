#include "MCategory.h"

MCategory* gCurrentMCategory = nullptr;

void MCategory::Init(int _posX, int _posY, int _sizeW, int _sizeH, int _borderSize, const std::string &_name, HFont _font)
{
	this->posX = _posX;
	this->posY = _posY;
	this->sizeW = _sizeW;
	this->sizeH = _sizeH;
	this->borderSize = _borderSize;
	this->name = _name;
	this->font = _font;
}

void MCategory::SetupColors(Color _color, Color _borderColorU, Color _borderColorR, Color _borderColorB, Color _borderColorL, Color _textColor, Color _nonActiveTextColor)
{
	this->color = _color;
	this->borderColorU = _borderColorU;
	this->borderColorR = _borderColorR;
	this->borderColorB = _borderColorB;
	this->borderColorL = _borderColorL;
	this->textColor = _textColor;
	this->nonActiveTextColor = _nonActiveTextColor;
}

void MCategory::AddChildControl(MBaseObject* _child)
{
	this->children.push_back(_child);
}

void MCategory::DeleteChildren()
{
	this->children.clear();
}

void MCategory::MakeDefaultCategory()
{
	if (!gCurrentMCategory)
	{
		gCurrentMCategory = this;
		this->active = true;
	}
}

void MCategory::Draw()
{
	if (gControls.OnClick(this->posX,this->posY, this->sizeW, this->sizeH))
	{
		if (gCurrentMCategory)
			gCurrentMCategory->active = false;

		this->active = true;
		gCurrentMCategory = this;
	}

	if (this->active)
	{
		//gPaint.DrawFilledRectWithBorder(this->posX, this->posY, this->sizeW, this->sizeH, this->borderSize, this->color, this->borderColorU, this->borderColorR, this->borderColorB, this->borderColorL);

		gPaint.DrawFilledRect(this->posX, this->posY, this->sizeW, this->sizeH, this->color);

		gPaint.DrawFilledRect(this->posX + this->borderSize, this->posY - this->borderSize, this->sizeW, this->borderSize, this->borderColorU);
		gPaint.DrawFilledRect(this->posX + this->sizeW, this->posY, this->borderSize, this->sizeH, this->borderColorR);
		gPaint.DrawFilledRect(this->posX + this->borderSize, this->posY + this->sizeH, this->sizeW, this->borderSize, this->borderColorB);
		gPaint.DrawFilledRect(this->posX, this->posY, this->borderSize, this->sizeH, this->borderColorL);

		gPaint.DrawString(this->posX + this->sizeW / 2, this->posY + this->sizeH / 2, 'c', this->name, this->font, this->textColor);
				
		for (const auto &child : this->children)
			child->Draw();
	}
	else
		gPaint.DrawString(this->posX + this->sizeW / 2, this->posY + this->sizeH / 2, 'c', this->name, this->font, this->nonActiveTextColor);
}