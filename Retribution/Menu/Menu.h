#pragma once
#include "MenuObjects\MWindow.h"
#include "MenuObjects\MCategory.h"
#include "MenuObjects\MCheckBox.h"
#include "MenuObjects\MSlider.h"
#include "..\SourceSDK\sdk.h"
#include "..\Features\LegitBot\LegitBot.h"
#include "..\Features\Visuals\Visuals.h"
#include "..\Features\Misc\Bhop.h"

class Menu
{
public:
	void DrawMenu();
	bool IsActive();
private:
	void SetupFonts();
	void GetMenuProportions();
	void Initialize();
	void SetupChilds();
	void SetupDefaults();
	void SetupElements();
private:
	bool active;
	bool isInitialized;
private:
	int menuPosistionX;
	int menuPosistionY;
	int menuSizeW;
	int menuSizeH;
	int categorySizeW;
	int categorySizeH;
	int menuBorder;
	int categoryBorder;
	int tabSizeW;
	int tabSizeH;
	int checkboxSize;
private:
	int resolutionW;
	int resolutionH;
private:
	struct Fonts
	{
		HFont category;
		HFont checkbox;
	} fonts;
private:
	struct Colors
	{
		Color menu{ 36, 36, 36, 255 };
		Color menuBorder{ 60, 60, 60, 255 };
		Color category{ 40,40,40,255 };
		Color nonActiveCategory{ 34, 34, 34, 255 };
		Color categoryBorder{ 50, 50, 50, 255 };
		Color text{ 255, 255, 255, 255 };
		Color nonActiveText{ 100, 100, 100, 255 };
		Color second{ 118, 6, 2, 255 };
		Color nonActiveCheckbox{ 60, 60, 60, 255 };
	} colors;
private:
	MWindow cheat;
	MWindow categories;
	MCategory legitBot;
	MCategory visuals;
	MCategory misc;
	MCheckBox sprayAssistActive;
	MSlider<float>sprayAssistLockFov;
	MSlider<float>sprayAssistUnlockFov;
	MSlider<int>sprayAssistStartBullet;
	MCheckBox backtrackingActive;
	MSlider<int>backtrackingMaxTick;
	MCheckBox VisualsActive;
	MCheckBox bhopActive;
};

extern Menu gMenu;
