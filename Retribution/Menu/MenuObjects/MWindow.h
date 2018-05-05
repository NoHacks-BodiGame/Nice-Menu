#pragma once
#include "MBaseObject.h"

class MWindow : public MBaseObject
{
public:
	MWindow() { };
	void Init(int _posX, int _posY, int _sizeW, int _sizeH, int _borderSize, const std::string &_name);
	void SetupColors(Color _color, Color _borderColor);
	void SetupColors(Color _color, Color _borderColorU, Color _borderColorR, Color _borderColorB, Color _borderColorL);
	void AddChildControl(MBaseObject* _child);
	void DeleteChildren();
	virtual void Draw() override;
private:
	std::vector<MBaseObject*>children;
};