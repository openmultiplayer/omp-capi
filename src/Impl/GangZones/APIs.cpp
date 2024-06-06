#include "../ComponentManager.hpp"

OMP_CAPI(GangZone_Create, objectPtr(float minx, float miny, float maxx, float maxy))
{
	IGangZonesComponent* component = ComponentManager::Get()->gangzones;
	if (component)
	{
		Vector2 min = { minx, miny };
		Vector2 max = { maxx, maxy };

		int id = component->reserveLegacyID();
		if (id == INVALID_GANG_ZONE_ID)
		{
			return nullptr;
		}

		GangZonePos pos;
		pos.min.x = truncf(min.x);
		pos.min.y = truncf(min.y);
		pos.max.x = truncf(max.x);
		pos.max.y = truncf(max.y);

		IGangZone* gz = component->create(pos);
		if (gz)
		{
			component->setLegacyID(id, gz->getID());
			return gz;
		}
		else
		{
			component->releaseLegacyID(id);
		}
	}
	return nullptr;
}

OMP_CAPI(GangZone_Destroy, bool(objectPtr gangzone))
{
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	gangzones->release(gz->getID());
	gangzones->releaseLegacyID(gangzones->toLegacyID(gz->getID()));
	return true;
}

OMP_CAPI(GangZone_ShowForPlayer, bool(objectPtr player, objectPtr gangzone, uint32_t color))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	gz->showForPlayer(*player_, Colour::FromRGBA(color));
	return true;
}

OMP_CAPI(GangZone_ShowForAll, bool(objectPtr gangzone, uint32_t color))
{
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	IPlayerPool* pool = ComponentManager::Get()->players;
	for (IPlayer* player : pool->entries())
	{
		gz->showForPlayer(*player, Colour::FromRGBA(color));
	}
	return true;
}

OMP_CAPI(GangZone_HideForPlayer, bool(objectPtr player, objectPtr gangzone))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	gz->hideForPlayer(*player_);
	return true;
}

OMP_CAPI(GangZone_HideForAll, bool(objectPtr gangzone))
{
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	IPlayerPool* pool = ComponentManager::Get()->players;
	for (IPlayer* player : pool->entries())
	{
		gz->hideForPlayer(*player);
	}
	return true;
}

OMP_CAPI(GangZone_FlashForPlayer, bool(objectPtr player, objectPtr gangzone, uint32_t color))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	gz->flashForPlayer(*player_, Colour::FromRGBA(color));
	return true;
}

OMP_CAPI(GangZone_FlashForAll, bool(objectPtr gangzone, uint32_t color))
{
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	IPlayerPool* pool = ComponentManager::Get()->players;
	for (IPlayer* player : pool->entries())
	{
		gz->flashForPlayer(*player, Colour::FromRGBA(color));
	}
	return true;
}

OMP_CAPI(GangZone_StopFlashForPlayer, bool(objectPtr player, objectPtr gangzone))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	gz->stopFlashForPlayer(*player_);
	return true;
}

OMP_CAPI(GangZone_StopFlashForAll, bool(objectPtr gangzone))
{
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	IPlayerPool* pool = ComponentManager::Get()->players;
	for (IPlayer* player : pool->entries())
	{
		gz->stopFlashForPlayer(*player);
	}
	return true;
}

OMP_CAPI(GangZone_IsValid, bool(objectPtr gangzone))
{
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	if(!gangzones->get(gz->getID())) return false;
	return true;
}

OMP_CAPI(GangZone_IsPlayerIn, bool(objectPtr player, objectPtr gangzone))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	return gz->isPlayerInside(*player_);
}

OMP_CAPI(GangZone_IsVisibleForPlayer, bool(objectPtr player, objectPtr gangzone))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	return gz->isShownForPlayer(*player_);
}

OMP_CAPI(GangZone_GetColorForPlayer, int(objectPtr player, objectPtr gangzone))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, 0);
	if (gz->isShownForPlayer(*player_))
	{
		return gz->getColourForPlayer(*player_).RGBA();
	}
	return 0;
}

OMP_CAPI(GangZone_GetFlashColorForPlayer, int(objectPtr player, objectPtr gangzone))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, 0);
	if (gz->isShownForPlayer(*player_))
	{
		return gz->getFlashingColourForPlayer(*player_).RGBA();
	}
	return 0;
}

OMP_CAPI(GangZone_IsFlashingForPlayer, bool(objectPtr player, objectPtr gangzone))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	return gz->isFlashingForPlayer(*player_);
}

OMP_CAPI(GangZone_GetPos, bool(objectPtr gangzone, float* minx, float* miny, float* maxx, float* maxy))
{
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	const GangZonePos& pos = gz->getPosition();
	*minx = pos.min.x;
	*miny = pos.min.y;
	*maxx = pos.max.x;
	*maxy = pos.max.y;
	return true;
}

OMP_CAPI(GangZone_UseCheck, bool(objectPtr gangzone, bool enable))
{
	POOL_ENTITY_RET(gangzones, IGangZone, gangzone, gz, false);
	gangzones->useGangZoneCheck(*gz, enable);
	return true;
}

/*
	Per-Player GangZones
*/
