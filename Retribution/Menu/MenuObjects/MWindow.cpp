#include "MWindow.h"

void MWindow::Init(int _posX, int _posY, int _sizeW, int _sizeH, int _borderSize, const std::string &_name)
{
	this->posX = _posX;
	this->posY = _posY;
	this->sizeW = _sizeW;
	this->sizeH = _sizeH;
	this->borderSize = _borderSize;
	this->name = _name;
}

void MWindow::SetupColors(Color _color, Color _borderColor)
{
	this->color = _color;
	this->borderColorU = _borderColor;
	this->borderColorR = _borderColor;
	this->borderColorB = _borderColor;
	this->borderColorL = _borderColor;
}

void MWindow::SetupColors(Color _color, Color _borderColorU, Color _borderColorR, Color _borderColorB, Color _borderColorL)
{
	this->color = _color;
	this->borderColorU = _borderColorU;
	this->borderColorR = _borderColorR;
	this->borderColorB = _borderColorB;
	this->borderColorL = _borderColorL;
}

void MWindow::AddChildControl(MBaseObject* _child)
{
	this->children.push_back(_child);
}

void MWindow::DeleteChildren()
{
	this->children.clear();
}

void MWindow::Draw()
{
	gPaint.DrawFilledRectWithBorder(this->posX, this->posY, this->sizeW, this->sizeH, this->borderSize, this->color, this->borderColorU, this->borderColorR, this->borderColorB, this->borderColorL);

	for (const auto &child : this->children)
		child->Draw();
}