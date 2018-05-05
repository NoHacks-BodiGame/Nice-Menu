#include "Visuals.h"

Visuals gVisuals;

bool Visuals::DrawEnemies(CBaseEntity* _localPlayer)
{
	if (gControls.Toggle(MOUSE_4))
		this->active = !this->active;

	if (!this->active)
		return false;

	for (int i = 0; i < gInterface.Engine()->GetMaxClients(); ++i)
	{
		CBaseEntity* entity = gInterface.EntityList()->GetClientEntity(i);

		if (!entity->IsValidTarget(_localPlayer, false, true, false, 0))
			continue;

		Vector bonePosition = entity->GetBonePosition(Bones::head);

		bonePosition.z += 15.f;

		Vector boneScreenPosition;
		
		if (!gMath.WorldToScreen(bonePosition, boneScreenPosition))
			continue;

		gPaint.DrawFilledRect(boneScreenPosition.x, boneScreenPosition.y, 2, 2, Color(178, 25, 72, 255));
	}

	return true;
}