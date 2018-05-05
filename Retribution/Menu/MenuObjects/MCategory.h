#pragma once
#include "MBaseObject.h"
#include "MWindow.h"

class MCategory : public MBaseObject
{
public:
	MCategory() { };
	void Init(int _posX, int _posY, int _sizeW, int _sizeH, int _borderSize, const std::string &_name, HFont _font);
	void SetupColors(Color _color, Color _borderColorU, Color _borderColorR, Color _borderColorB, Color _borderColorL, Color _textColor, Color _nonActiveTextColor);
	void AddChildControl(MBaseObject* _child);
	void DeleteChildren();
	void MakeDefaultCategory();
	virtual void Draw() override;
private:
	HFont font;
	Color textColor{ 255,255,255,100 };
	Color nonActiveTextColor{ 255,255,255,255 };
	std::vector<MBaseObject*>children;
};

extern MCategory* gCurrentMCategory;