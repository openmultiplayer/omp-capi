#include "../ComponentManager.hpp"

OMP_CAPI(Pickup_Create, objectPtr(int model, int type, float x, float y, float z, int virtualWorld))
{
	IPickupsComponent* component = ComponentManager::Get()->pickups;
	if (component)
	{
		int id = component->reserveLegacyID();
		if (id == INVALID_PICKUP_ID)
		{
			return nullptr;
		}

		IPickup* pickup = component->create(model, type, { x, y, z }, virtualWorld, false);
		if (pickup)
		{
			component->setLegacyID(id, pickup->getID());
			return pickup;
		}
		else
		{
			component->releaseLegacyID(id);
		}
	}
	return nullptr;
}

OMP_CAPI(Pickup_AddStatic, bool(int model, int type, float x, float y, float z, int virtualWorld))
{
	IPickupsComponent* component = ComponentManager::Get()->pickups;
	if (component)
	{
		int id = component->reserveLegacyID();
		if (id == INVALID_PICKUP_ID)
		{
			return nullptr;
		}

		IPickup* pickup = component->create(model, type, { x, y, z }, virtualWorld, true);
		if (pickup)
		{
			component->setLegacyID(id, pickup->getID());
			return pickup;
		}
		else
		{
			component->releaseLegacyID(id);
		}
	}
	return false;
}

OMP_CAPI(Pickup_Destroy, bool(objectPtr pickup))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	pickups->release(p->getID());
	pickups->releaseLegacyID(pickups->toLegacyID(p->getID()));
	return true;
}

OMP_CAPI(Pickup_IsValid, bool(objectPtr pickup))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	if (!pickups->get(p->getID()))
		return false;
	return true;
}

OMP_CAPI(Pickup_IsStreamedIn, bool(objectPtr player, objectPtr pickup))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	return p->isStreamedInForPlayer(*player_);
}

OMP_CAPI(Pickup_GetPos, bool(objectPtr pickup, float* x, float* y, float* z))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	auto pos = p->getPosition();
	return true;
}

OMP_CAPI(Pickup_GetModel, int(objectPtr pickup))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, 0);
	return p->getModel();
}

OMP_CAPI(Pickup_GetType, int(objectPtr pickup))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, -1);
	return p->getType();
}

OMP_CAPI(Pickup_GetVirtualWorld, int(objectPtr pickup))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, 0);
	return p->getVirtualWorld();
}

OMP_CAPI(Pickup_SetPos, bool(objectPtr pickup, float x, float y, float z, bool update))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	if (update)
	{
		p->setPosition({ x, y, z });
	}
	else
	{
		p->setPositionNoUpdate({ x, y, z });
	}
	return true;
}

OMP_CAPI(Pickup_SetModel, bool(objectPtr pickup, int model, bool update))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	p->setModel(model, update);
	return true;
}

OMP_CAPI(Pickup_SetType, bool(objectPtr pickup, int type, bool update))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	p->setType(type, update);
	return true;
}

OMP_CAPI(Pickup_SetVirtualWorld, bool(objectPtr pickup, int virtualworld))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	p->setVirtualWorld(virtualworld);
	return true;
}

OMP_CAPI(Pickup_ShowForPlayer, bool(objectPtr player, objectPtr pickup))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	p->setPickupHiddenForPlayer(*player_, false);
	return true;
}

OMP_CAPI(Pickup_HideForPlayer, bool(objectPtr player, objectPtr pickup))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	p->setPickupHiddenForPlayer(*player_, true);
	return true;
}

OMP_CAPI(Pickup_IsHiddenForPlayer, bool(objectPtr player, objectPtr pickup))
{
	POOL_ENTITY_RET(pickups, IPickup, pickup, p, false);
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	return p->isPickupHiddenForPlayer(*player_);
}
