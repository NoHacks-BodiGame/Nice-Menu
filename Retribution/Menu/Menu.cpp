#include "Menu.h"

Menu gMenu;

void Menu::DrawMenu()
{
	if (gControls.Toggle(KEY_INSERT))
	{
		this->active = !this->active;
			
		std::ostringstream mouseEnableCmd;
		mouseEnableCmd << "cl_mouseenable " << std::setw(1) << std::setfill('0') << !this->active;
		gInterface.Engine()->ClientCmd(mouseEnableCmd.str().c_str());
	}
	
	if (this->active)
	{
		static int oldResolutionW = 0;
		static int oldResolutionH = 0;

		gInterface.Engine()->GetScreenSize(this->resolutionW, this->resolutionH);

		if (this->resolutionW != oldResolutionW || this->resolutionH != oldResolutionH)
		{
			this->SetupFonts();
			this->GetMenuProportions();
			this->SetupElements();

			oldResolutionW = this->resolutionW;
			oldResolutionH = this->resolutionH;
		}
		
		if (!this->isInitialized)
		{
			this->Initialize();
			this->isInitialized = true;
		}
				
		this->cheat.Draw();
		gPaint.DrawCursor(Color(255, 255, 255, 255), Color(0, 0, 0, 255));
	}
}

void Menu::SetupFonts()
{
	this->fonts.category = gPaint.SetupFont(this->resolutionH / 32, "badcache", FONTFLAG_ANTIALIAS | FONTFLAG_ADDITIVE);
	this->fonts.checkbox = gPaint.SetupFont(this->resolutionH / 45, "Segoe UI", FONTFLAG_ANTIALIAS | FONTFLAG_ADDITIVE);
}

void Menu::GetMenuProportions()
{
	this->menuSizeW = this->resolutionW / 3;
	this->menuSizeH = this->resolutionH / 2;
	this->menuPosistionX = this->resolutionW / 2 - this->menuSizeW / 2;
	this->menuPosistionY = this->resolutionH / 2 - this->menuSizeH / 2;
	this->categorySizeW = this->menuSizeW / 3;
	this->categorySizeH = this->menuSizeH / 6;
	this->menuBorder = 6;
	this->categoryBorder = 2;
	this->tabSizeW = (this->menuSizeW * 2 / 3 - this->categoryBorder) / 5;
	this->tabSizeH = this->menuSizeH / 12;
	this->checkboxSize = this->menuSizeH / 32;
}

void Menu::Initialize()
{
	this->SetupChilds();
	this->SetupDefaults();
	this->SetupElements();
}

void Menu::SetupElements()
{
	this->cheat.Init(this->menuPosistionX, this->menuPosistionY, this->menuSizeW, this->menuSizeH, this->menuBorder, "Retribution v2");
	this->cheat.SetupColors(this->colors.menu, this->colors.menuBorder);

	this->categories.Init(this->menuPosistionX, this->menuPosistionY, this->categorySizeW, this->menuSizeH, 1, "Categories");
	this->categories.SetupColors(this->colors.nonActiveCategory, this->colors.menuBorder, Color(80,80,80,255), this->colors.menuBorder, this->colors.menuBorder);

	this->legitBot.Init(this->menuPosistionX, this->menuPosistionY + this->categorySizeH / 2, this->categorySizeW, this->categorySizeH, this->categoryBorder, "A", this->fonts.category);
	this->legitBot.SetupColors(this->colors.category, Color(0,0,0,0), Color(0, 0, 0, 0), Color(0, 0, 0, 0), this->colors.second, this->colors.text, this->colors.nonActiveText);

	this->visuals.Init(this->menuPosistionX, this->menuPosistionY + this->categorySizeH * 3 / 2, this->categorySizeW, this->categorySizeH, this->categoryBorder, "D", this->fonts.category);
	this->visuals.SetupColors(this->colors.category, Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0), this->colors.second, this->colors.text, this->colors.nonActiveText);

	this->misc.Init(this->menuPosistionX, this->menuPosistionY + this->categorySizeH * 5 / 2, this->categorySizeW, this->categorySizeH, this->categoryBorder, "G", this->fonts.category);
	this->misc.SetupColors(this->colors.category, Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0), this->colors.second, this->colors.text, this->colors.nonActiveText);


	this->backtrackingActive.Init(this->menuPosistionX + this->categorySizeW + (this->menuPosistionX - this->categorySizeW) / 3, (int)(this->menuPosistionY + this->menuSizeH / 6.75), this->checkboxSize, 2, &gLegitBot.backtracking.active, "Backtracking", this->fonts.checkbox);
	this->backtrackingActive.SetupColors(this->colors.second, this->colors.text, this->colors.nonActiveCheckbox);
		 
	this->backtrackingMaxTick.Init(this->menuPosistionX + this->categorySizeW + (this->menuPosistionX - this->categorySizeW) / 3, (int)(this->menuPosistionY + this->menuSizeH / 4.5), this->menuSizeW / 3, this->checkboxSize, &gLegitBot.maxTick, 1, 12, 0, "Max tick", this->fonts.checkbox);
	this->backtrackingMaxTick.SetupColors(this->colors.second, this->colors.text, this->colors.nonActiveCheckbox);

	this->bhopActive.Init(this->menuPosistionX + this->categorySizeW + (this->menuPosistionX - this->categorySizeW) / 3, (int)(this->menuPosistionY + this->menuSizeH / 6.75), this->checkboxSize, 2, &gBhop.active, "Bhop", this->fonts.checkbox);
	this->bhopActive.SetupColors(this->colors.second, this->colors.text, this->colors.nonActiveCheckbox);
}

void Menu::SetupChilds()
{
	this->cheat.AddChildControl(&this->categories);
	this->categories.AddChildControl(&this->legitBot);
	this->categories.AddChildControl(&this->visuals);
	this->categories.AddChildControl(&this->misc);
	this->legitBot.AddChildControl(&this->sprayAssistActive);
	this->legitBot.AddChildControl(&this->sprayAssistLockFov);
	this->legitBot.AddChildControl(&this->sprayAssistUnlockFov);
	this->legitBot.AddChildControl(&this->sprayAssistStartBullet);
	this->legitBot.AddChildControl(&this->backtrackingActive);
	this->legitBot.AddChildControl(&this->backtrackingMaxTick);
	this->visuals.AddChildControl(&this->VisualsActive);
	this->misc.AddChildControl(&this->bhopActive);
}

void Menu::SetupDefaults()
{
	this->legitBot.MakeDefaultCategory();
}

bool Menu::IsActive()
{
	return this->active;
}