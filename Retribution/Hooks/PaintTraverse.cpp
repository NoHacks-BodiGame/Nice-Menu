#include "Hooks.h"

Hook::PaintTraverseFn Hook::OriginalPaintTraverse;

VPANEL MatSystemTopPanel = 0;

void __stdcall Hook::HookedPaintTraverse(VPANEL _vguiPanel, bool _forceRepaint, bool _allowForce)
{
	OriginalPaintTraverse(_vguiPanel, _forceRepaint, _allowForce);
	
	if (!MatSystemTopPanel && !strcmp(gInterface.Panel()->GetName(_vguiPanel), "MatSystemTopPanel"))
		MatSystemTopPanel = _vguiPanel;
		
	if (_vguiPanel == MatSystemTopPanel)
	{
		gMenu.DrawMenu();

		CBaseEntity* localPlayer = gInterface.EntityList()->GetClientEntity(gInterface.Engine()->GetLocalPlayer());

		if(localPlayer)
			gVisuals.DrawEnemies(localPlayer);
	}

}