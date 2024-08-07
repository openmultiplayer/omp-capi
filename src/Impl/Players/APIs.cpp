/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, open.mp team and contributors.
 */

#include "../ComponentManager.hpp"

OMP_CAPI(Player_FromID, objectPtr(int playerid))
{
	IPlayerPool* component = ComponentManager::Get()->players;
	if (component)
	{
		return component->get(playerid);
	}
	return nullptr;
}

OMP_CAPI(Player_GetID, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, INVALID_PLAYER_ID);
	return player_->getID();
}

OMP_CAPI(Player_SendClientMessage, void(objectPtr player, uint32_t color, StringCharPtr text))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->sendClientMessage(Colour::FromRGBA(color), text);
}

OMP_CAPI(All_SendClientMessage, void(uint32_t color, StringCharPtr text))
{
	ComponentManager::Get()->players->sendClientMessageToAll(Colour::FromRGBA(color), text);
}

OMP_CAPI(Player_SetCameraPosition, void(objectPtr player, float x, float y, float z))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setCameraPosition({ x, y, z });
}

OMP_CAPI(Player_SetDrunkLevel, void(objectPtr player, int level))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setDrunkLevel(level);
}

OMP_CAPI(Player_SetInterior, void(objectPtr player, unsigned interior))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setInterior(interior);
}

OMP_CAPI(Player_SetWantedLevel, void(objectPtr player, unsigned int level))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setWantedLevel(level);
}

OMP_CAPI(Player_SetWeather, void(objectPtr player, int weather))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setWeather(weather);
}

OMP_CAPI(Player_GetWeather, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	int weather = player_->getWeather();
	return weather;
}

OMP_CAPI(Player_SetSkin, void(objectPtr player, int skin))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setSkin(skin);
}

OMP_CAPI(Player_SetShopName, void(objectPtr player, StringCharPtr name))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setShopName(name);
}

OMP_CAPI(Player_GetShopName, void(objectPtr player, OutputStringViewPtr name))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto result = player_->getShopName();
	COPY_STRING_TO_CAPI_STRING_VIEW(name, result.data(), result.length());
}

OMP_CAPI(Player_GiveMoney, void(objectPtr player, int amount))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->giveMoney(amount);
}

OMP_CAPI(Player_SetCameraLookAt, void(objectPtr player, float x, float y, float z, int cutType))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setCameraLookAt({ x, y, z }, cutType);
}

OMP_CAPI(Player_GetCameraLookAt, void(objectPtr player, float* x, float* y, float* z))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto pos = player_->getCameraLookAt();
	*x = pos.x;
	*y = pos.y;
	*z = pos.z;
}

OMP_CAPI(Player_SetCameraBehind, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setCameraBehind();
}

OMP_CAPI(Player_CreateExplosion, void(objectPtr player, float x, float y, float z, int type, float radius))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->createExplosion({ x, y, z }, type, radius);
}

OMP_CAPI(All_CreateExplosion, void(float x, float y, float z, int type, float radius))
{
	ComponentManager::Get()->players->createExplosionForAll({ x, y, z }, type, radius);
}

OMP_CAPI(Player_PlayAudio, void(objectPtr player, StringCharPtr url, bool usePos, float x, float y, float z, float distance))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->playAudio(url, usePos, { x, y, z }, distance);
}

OMP_CAPI(Player_StopAudio, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->stopAudio();
}

OMP_CAPI(All_SendDeathMessage, void(objectPtr killer, objectPtr killee, int weapon))
{
	if (killee)
	{
		POOL_ENTITY(players, IPlayer, killer, killer_);
		ENTITY_CAST(IPlayer, killee, killee_);
		ComponentManager::Get()->players->sendDeathMessageToAll(killer_, *killee_, weapon);
	}
	else
	{
		ComponentManager::Get()->players->sendEmptyDeathMessageToAll();
	}
}

OMP_CAPI(Player_UseWidescreen, void(objectPtr player, bool enable))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->useWidescreen(enable);
}

OMP_CAPI(Player_HasWidescreen, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	auto enabled = player_->hasWidescreen();
	return enabled;
}

OMP_CAPI(Player_SetHealth, void(objectPtr player, float health))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setHealth(health);
}

OMP_CAPI(Player_GetHealth, float(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0.0f);
	auto health = player_->getHealth();
	return health;
}

OMP_CAPI(Player_SetArmor, void(objectPtr player, float armor))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setArmour(armor);
}

OMP_CAPI(Player_GetArmor, float(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0.0f);
	float armor = player_->getArmour();
	return armor;
}

OMP_CAPI(Player_SetTeam, void(objectPtr player, int team))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setTeam(team);
}

OMP_CAPI(Player_GetTeam, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	auto team = player_->getTeam();
	return team;
}

OMP_CAPI(Player_SetScore, void(objectPtr player, int score))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setScore(score);
}

OMP_CAPI(Player_GetScore, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	auto score = player_->getScore();
	return score;
}

OMP_CAPI(Player_GetSkin, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	auto skin = player_->getSkin();
	return skin;
}

OMP_CAPI(Player_SetColor, void(objectPtr player, uint32_t color))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setColour(Colour::FromRGBA(color));
}

OMP_CAPI(Player_GetColor, uint32_t(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	auto color = player_->getColour().RGBA();
	return color;
}

OMP_CAPI(Player_GetDefaultColor, uint32_t(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	// The player doesn't need to be connected for this to work.
	auto color = ComponentManager::Get()->players->getDefaultColour(player_->getID()).RGBA();
	return color;
}

OMP_CAPI(Player_GetDrunkLevel, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	auto level = player_->getDrunkLevel();
	return level;
}

OMP_CAPI(Player_GiveWeapon, void(objectPtr player, uint8_t weapon, uint32_t ammo))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	WeaponSlotData data;
	data.id = weapon;
	data.ammo = ammo;
	player_->giveWeapon(data);
}

OMP_CAPI(Player_RemoveWeapon, void(objectPtr player, uint8_t weapon))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->removeWeapon(weapon);
}

OMP_CAPI(Player_SetMoney, void(objectPtr player, int money))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setMoney(money);
}

OMP_CAPI(Player_GetMoney, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	auto money = player_->getMoney();
	return money;
}

OMP_CAPI(Player_ResetMoney, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->resetMoney();
}

OMP_CAPI(Player_SetName, int(objectPtr player, StringCharPtr name))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	int status = int(player_->setName(name));
	return status;
}

OMP_CAPI(Player_GetName, void(objectPtr player, OutputStringViewPtr name))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto result = player_->getName();
	COPY_STRING_TO_CAPI_STRING_VIEW(name, result.data(), result.length());
}

OMP_CAPI(Player_GetState, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	int state = player_->getState();
	return state;
}

OMP_CAPI(Player_GetPing, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	int ping = player_->getPing();
	return ping;
}

OMP_CAPI(Player_GetArmedWeapon, uint32_t(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	uint32_t weapon = player_->getArmedWeapon();
	return weapon;
}

OMP_CAPI(Player_SetTime, void(objectPtr player, int hour, int minute))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setTime(std::chrono::hours(hour), std::chrono::minutes(minute));
}

OMP_CAPI(Player_GetTime, void(objectPtr player, int* hour, int* minute))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto data = player_->getTime();
	*hour = data.first.count();
	*minute = data.second.count();
}

OMP_CAPI(Player_SetWorldTime, void(objectPtr player, int time))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setWorldTime(std::chrono::hours(time));
}

OMP_CAPI(Player_UseClock, void(objectPtr player, bool enable))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->useClock(enable);
}

OMP_CAPI(Player_HasClock, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	auto enable = player_->hasClock();
	return enable;
}

OMP_CAPI(Player_ForceClassSelection, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->forceClassSelection();
}

OMP_CAPI(Player_GetWantedLevel, unsigned(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	auto wanted = player_->getWantedLevel();
	return wanted;
}

OMP_CAPI(Player_SetFightingStyle, void(objectPtr player, int style))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setFightingStyle(PlayerFightingStyle(style));
}

OMP_CAPI(Player_GetFightingStyle, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	int style = int(player_->getFightingStyle());
	return style;
}

OMP_CAPI(Player_SetVelocity, void(objectPtr player, float x, float y, float z))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setVelocity({ x, y, z });
}

OMP_CAPI(Player_GetVelocity, void(objectPtr player, float* x, float* y, float* z))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto velocity = player_->getVelocity();
	*x = velocity.x;
	*y = velocity.y;
	*z = velocity.z;
}

OMP_CAPI(Player_GetAimData, void(objectPtr player, float* frontVectorX, float* frontVectorY, float* frontVectorZ, float* posX, float* posY, float* posZ, float* aimZ, float* camZoom, float* aspectRatio, int8_t* weaponState, uint8_t* camMode))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto data = player_->getAimData();
	*frontVectorX = data.camFrontVector.x;
	*frontVectorY = data.camFrontVector.y;
	*frontVectorZ = data.camFrontVector.z;
	*posX = data.camPos.x;
	*posY = data.camPos.y;
	*posZ = data.camPos.z;
	*aimZ = data.aimZ;
	*camZoom = data.camZoom;
	*aspectRatio = data.aspectRatio;
	*weaponState = data.weaponState;
	*camMode = data.camMode;
}

OMP_CAPI(Player_GetDistanceFromPoint, float(objectPtr player, float x, float y, float z))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0.0f);
	Vector3 playerCoords = player_->getPosition();
	float distance = glm::distance(playerCoords, { x, y, z });
	return distance;
}

OMP_CAPI(Player_GetInterior, unsigned(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	unsigned interior = player_->getInterior();
	return interior;
}

OMP_CAPI(Player_SetPosition, void(objectPtr player, float x, float y, float z))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setPosition({ x, y, z });
}

OMP_CAPI(Player_GetPosition, void(objectPtr player, float* x, float* y, float* z))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto pos = player_->getPosition();
	*x = pos.x;
	*y = pos.y;
	*z = pos.z;
}

OMP_CAPI(Player_GetVirtualWorld, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	int vw = player_->getVirtualWorld();
	return vw;
}

OMP_CAPI(Player_IsBot, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	auto bot = player_->isBot();
	return bot;
}

OMP_CAPI(Player_IsStreamedInForPlayer, bool(objectPtr player, objectPtr other))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	ENTITY_CAST_RET(IPlayer, other, other_, false);
	bool streamed = player_->isStreamedInForPlayer(*other_);
	return streamed;
}

OMP_CAPI(Player_PlaySound, void(objectPtr player, uint32_t sound, float x, float y, float z))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->playSound(sound, { x, y, z });
}

OMP_CAPI(Player_LastPlayedSound, uint32_t(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	return player_->lastPlayedSound();
}

OMP_CAPI(Player_SpectatePlayer, void(objectPtr player, objectPtr target, int mode))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	ENTITY_CAST(IPlayer, target, target_);
	player_->spectatePlayer(*target_, PlayerSpectateMode(mode));
}

OMP_CAPI(Player_SpectateVehicle, void(objectPtr player, objectPtr target, int mode))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	POOL_ENTITY(vehicles, IVehicle, target, target_);
	player_->spectateVehicle(*target_, PlayerSpectateMode(mode));
}

OMP_CAPI(Player_SetVirtualWorld, void(objectPtr player, int vw))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setVirtualWorld(vw);
}

OMP_CAPI(Player_SetWorldBounds, void(objectPtr player, float xMax, float xMin, float yMax, float yMin))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	Vector4 coords = { xMax, xMin, yMax, yMin };
	player_->setWorldBounds(coords);
}

OMP_CAPI(Player_GetWorldBounds, void(objectPtr player, float* xmax, float* xmin, float* ymax, float* ymin))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto bounds = player_->getWorldBounds();
	*xmax = bounds.x;
	*xmin = bounds.y;
	*ymax = bounds.z;
	*ymin = bounds.w;
}

OMP_CAPI(Player_ClearTasks, void(objectPtr player, int syncType))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->clearTasks(PlayerAnimationSyncType(syncType));
}

OMP_CAPI(Player_GetBulletData, void(objectPtr player, float* originX, float* originY, float* originZ, float* hitX, float* hitY, float* hitZ, float* offsetX, float* offsetY, float* offsetZ, uint8_t* weapon, int* hitType, uint16_t* hitID))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PlayerBulletData data = player_->getBulletData();

	*originX = data.origin.x;
	*originY = data.origin.y;
	*originZ = data.origin.z;

	*hitX = data.hitPos.x;
	*hitY = data.hitPos.y;
	*hitZ = data.hitPos.z;

	*offsetX = data.offset.x;
	*offsetY = data.offset.y;
	*offsetZ = data.offset.z;

	*weapon = data.weapon;
	*hitType = data.hitType;
	*hitID = data.hitID;
}

OMP_CAPI(Player_GetCameraTargetPlayer, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	return player_->getCameraTargetPlayer();
}

OMP_CAPI(Player_GetCameraTargetActor, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	return player_->getCameraTargetActor();
}

OMP_CAPI(Player_GetCameraTargetObject, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	return player_->getCameraTargetObject();
}

OMP_CAPI(Player_GetCameraTargetVehicle, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	return player_->getCameraTargetVehicle();
}

OMP_CAPI(Player_PutInVehicle, void(objectPtr player, objectPtr vehicle, int seat))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	POOL_ENTITY(vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->putPlayer(*player_, seat);
}

OMP_CAPI(Player_RemoveDefaultObjects, void(objectPtr player, unsigned model, float x, float y, float z, float radius))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->removeDefaultObjects(model, { x, y, z }, radius);
}

OMP_CAPI(Player_GetDefaultObjectsRemoved, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	return player_->getDefaultObjectsRemoved();
}

OMP_CAPI(Player_RemoveFromVehicle, void(objectPtr player, bool force))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->removeFromVehicle(force);
}

OMP_CAPI(Player_UnsetMapIcon, void(objectPtr player, int icon))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->unsetMapIcon(icon);
}

OMP_CAPI(Player_SetMapIcon, void(objectPtr player, int iconID, float x, float y, float z, int type, uint32_t color, int style))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setMapIcon(iconID, { x, y, z }, type, Colour::FromRGBA(color), MapIconStyle(style));
}

OMP_CAPI(Player_ResetWeapons, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->resetWeapons();
}

OMP_CAPI(Player_SetWeaponAmmo, void(objectPtr player, uint8_t id, uint32_t ammo))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	WeaponSlotData data;
	data.id = id;
	data.ammo = ammo;
	player_->setWeaponAmmo(data);
}

OMP_CAPI(Player_SetArmedWeapon, void(objectPtr player, uint32_t weapon))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setArmedWeapon(weapon);
}

OMP_CAPI(Player_SetChatBubble, void(objectPtr player, StringCharPtr text, uint32_t color, float drawdistance, int expiretime))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setChatBubble(text, Colour::FromRGBA(color), drawdistance, std::chrono::milliseconds(expiretime));
}

OMP_CAPI(Player_SetPositionFindZ, void(objectPtr player, float x, float y, float z))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setPositionFindZ({ x, y, z });
}

OMP_CAPI(Player_SetSkillLevel, void(objectPtr player, uint8_t weapon, int level))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setSkillLevel(PlayerWeaponSkill(weapon), level);
}

OMP_CAPI(Player_SetAction, void(objectPtr player, int action))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setAction(PlayerSpecialAction(action));
}

OMP_CAPI(Player_ToggleOtherNameTag, void(objectPtr player, objectPtr other, bool enable))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	ENTITY_CAST(IPlayer, other, other_);
	player_->toggleOtherNameTag(*other_, enable);
}

OMP_CAPI(Player_SetControllable, void(objectPtr player, bool enable))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setControllable(enable);
}

OMP_CAPI(Player_SetSpectating, void(objectPtr player, bool enable))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setSpectating(enable);
}

OMP_CAPI(Player_ApplyAnimation, void(objectPtr player, float delta, bool loop, bool lockX, bool lockY, bool freeze, uint32_t time, StringCharPtr animlib, StringCharPtr animname, int sync))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	AnimationData animationData(delta, loop, lockX, lockY, freeze, time, animlib, animname);
	player_->applyAnimation(animationData, PlayerAnimationSyncType(sync));
}

OMP_CAPI(Player_GetAnimationName, void(int index, OutputStringViewPtr lib, OutputStringViewPtr name))
{
	Pair<StringView, StringView> anim = splitAnimationNames(index);
	SET_CAPI_STRING_VIEW(lib, anim.first);
	SET_CAPI_STRING_VIEW(name, anim.second);
}

OMP_CAPI(Player_EditAttachedObject, void(objectPtr player, int index))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerObjectData, data);
	data->editAttachedObject(index);
}

OMP_CAPI(Player_UseCameraTargetting, void(objectPtr player, bool enable))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->useCameraTargeting(enable);
}

OMP_CAPI(Player_UseStuntBonuses, void(objectPtr player, bool enable))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->useStuntBonuses(enable);
}

OMP_CAPI(All_EnableStuntBonus, void(bool enable))
{
	ComponentManager::Get()->core->useStuntBonuses(enable);
}

OMP_CAPI(Player_GetArmedWeaponAmmo, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	int ammo = player_->getArmedWeaponAmmo();
	return ammo;
}

OMP_CAPI(Player_GetAnimationData, void(objectPtr player, uint16_t* id, uint16_t* flags))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto data = player_->getAnimationData();
	*id = data.ID;
	*flags = data.flags;
}

OMP_CAPI(Player_GetFacingAngle, float(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0.0f);
	GTAQuat quat = player_->getRotation();
	float angle = quat.ToEuler().z;
	return angle;
}

OMP_CAPI(Player_GetIp, void(objectPtr player, OutputStringViewPtr ip))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PeerNetworkData data = player_->getNetworkData();
	if (!data.networkID.address.ipv6)
	{
		PeerAddress::AddressString addressString;
		if (PeerAddress::ToString(data.networkID.address, addressString))
		{
			auto len = addressString.length();
			COPY_STRING_TO_CAPI_STRING_VIEW(ip, addressString.data(), len);
			return;
		}
	}
	return;
}

OMP_CAPI(Player_GetAction, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	int action = player_->getAction();
	return action;
}

OMP_CAPI(Player_GetVehicle, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	PLAYER_DATA_RET(player_, IPlayerVehicleData, data, nullptr);
	IVehicle* vehicle = data->getVehicle();
	return vehicle;
}

OMP_CAPI(Player_GetVehicleSeat, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	PLAYER_DATA_RET(player_, IPlayerVehicleData, data, 0);
	return data->getSeat();
}

OMP_CAPI(Player_GetWeaponSlot, void(objectPtr player, int slot, uint8_t* weapon, uint32_t* ammo))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	const WeaponSlotData& weaponSlot = player_->getWeaponSlot(slot);
	*weapon = weaponSlot.id;
	*ammo = weaponSlot.ammo;
}

OMP_CAPI(Player_InterpolateCameraPosition, void(objectPtr player, float from_x, float from_y, float from_z, float to_x, float to_y, float to_z, int time, int cut))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->interpolateCameraPosition({ from_x, from_y, from_z }, { to_x, to_y, to_z }, time, PlayerCameraCutType(cut));
}

OMP_CAPI(Player_InterpolateCameraLookAt, void(objectPtr player, float from_x, float from_y, float from_z, float to_x, float to_y, float to_z, int time, int cut))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->interpolateCameraLookAt({ from_x, from_y, from_z }, { to_x, to_y, to_z }, time, PlayerCameraCutType(cut));
}

OMP_CAPI(Player_HasAttachedObject, bool(objectPtr player, int index))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_DATA_RET(player_, IPlayerObjectData, data, false);
	bool ret = data->hasAttachedObject(index);
	return ret;
}

OMP_CAPI(Player_AttachCameraToObject, void(objectPtr player, objectPtr object))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	POOL_ENTITY(objects, IObject, object, object_);
	player_->attachCameraToObject(*object_);
}

OMP_CAPI(Player_AttachCameraToPlayerObject, void(objectPtr player, objectPtr object))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_POOL_ENTITY(player_, IPlayerObjectData, IPlayerObject, object, object_);
	player_->attachCameraToObject(*object_);
}

OMP_CAPI(Player_GetKeyData, void(objectPtr player, uint32_t* keys, int16_t* updown, int16_t* leftright))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	const PlayerKeyData& keyData = player_->getKeyData();
	*keys = keyData.keys;
	*updown = keyData.upDown;
	*leftright = keyData.leftRight;
}

OMP_CAPI(Player_GetSurfingVehicle, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	PlayerSurfingData data = player_->getSurfingData();
	if (player_->getState() == PlayerState_OnFoot && data.type == PlayerSurfingData::Type::Vehicle)
	{
		IVehiclesComponent* vehicles = ComponentManager::Get()->vehicles;
		if (vehicles)
		{
			return vehicles->get(data.ID);
		}
	}
	return nullptr;
}

OMP_CAPI(Player_GetSurfingObject, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	PlayerSurfingData data = player_->getSurfingData();
	if (player_->getState() == PlayerState_OnFoot && data.type == PlayerSurfingData::Type::Object)
	{
		IObjectsComponent* objects = ComponentManager::Get()->objects;
		if (objects)
		{
			return objects->get(data.ID);
		}
	}
	return nullptr;
}

OMP_CAPI(Player_GetTargetPlayer, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	IPlayer* target = player_->getTargetPlayer();
	return target;
}

OMP_CAPI(Player_GetTargetActor, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	return player_->getTargetActor();
}

OMP_CAPI(Player_IsInRangeOfPoint, bool(objectPtr player, float range, float x, float y, float z))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	bool ret = bool(range >= glm::distance(player_->getPosition(), { x, y, z }));
	return ret;
}

OMP_CAPI(Player_PlayCrimeReport, bool(objectPtr player, objectPtr suspect, int crime))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	ENTITY_CAST_RET(IPlayer, suspect, suspect_, false);
	return player_->playerCrimeReport(*suspect_, crime);
}

OMP_CAPI(Player_RemoveAttachedObject, void(objectPtr player, int index))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerObjectData, data);
	data->removeAttachedObject(index);
}

OMP_CAPI(Player_SetAttachedObject, void(objectPtr player, int index, int modelid, int bone, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ, float scaleX, float scaleY, float scaleZ, uint32_t materialcolor1, uint32_t materialcolor2))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerObjectData, data);
	ObjectAttachmentSlotData attachment;
	attachment.model = modelid;
	attachment.bone = bone;
	attachment.offset = { offsetX, offsetY, offsetZ };
	attachment.rotation = { rotationX, rotationY, rotationZ };
	attachment.scale = { scaleX, scaleY, scaleZ };
	attachment.colour1 = Colour::FromARGB(materialcolor1);
	attachment.colour2 = Colour::FromARGB(materialcolor2);
	data->setAttachedObject(index, attachment);
}

OMP_CAPI(Player_GetAttachedObject, void(objectPtr player, int index, int* modelid, int* bone, float* offsetX, float* offsetY, float* offsetZ, float* rotationX, float* rotationY, float* rotationZ, float* scaleX, float* scaleY, float* scaleZ, uint32_t* materialcolor1, uint32_t* materialcolor2))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerObjectData, data);
	ObjectAttachmentSlotData attachment = data->getAttachedObject(index);
	*modelid = attachment.model;
	*bone = attachment.bone;
	*offsetX = attachment.offset.x;
	*offsetY = attachment.offset.y;
	*offsetZ = attachment.offset.z;
	*rotationX = attachment.rotation.x;
	*rotationY = attachment.rotation.y;
	*rotationZ = attachment.rotation.z;
	*scaleX = attachment.scale.x;
	*scaleY = attachment.scale.y;
	*scaleZ = attachment.scale.z;
	*materialcolor1 = attachment.colour1.ARGB();
	*materialcolor2 = attachment.colour2.ARGB();
}

OMP_CAPI(Player_SetFacingAngle, void(objectPtr player, float angle))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	Vector3 rotation = player_->getRotation().ToEuler();
	rotation.z = angle;
	player_->setRotation(rotation);
}

OMP_CAPI(Player_SetOtherColor, void(objectPtr player, objectPtr other, uint32_t color))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	ENTITY_CAST(IPlayer, other, other_);
	player_->setOtherColour(*other_, Colour::FromRGBA(color));
}

OMP_CAPI(Player_GetOtherColor, bool(objectPtr player, objectPtr other))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	ENTITY_CAST_RET(IPlayer, other, other_, false);
	Colour color;
	bool hasPlayerSpecificColor = player_->getOtherColour(*other_, color);
	return hasPlayerSpecificColor;
}

OMP_CAPI(Player_AllowTeleport, void(objectPtr player, bool allow))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->allowTeleport(allow);
}

OMP_CAPI(Player_IsTeleportAllowed, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	return player_->isTeleportAllowed();
}

OMP_CAPI(Player_SetRemoteVehicleCollisions, void(objectPtr player, bool enable))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setRemoteVehicleCollisions(enable);
}

OMP_CAPI(Player_BeginTextDrawSelection, void(objectPtr player, uint32_t hoverColour))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerTextDrawData, data);
	data->beginSelection(Colour::FromRGBA(hoverColour));
}

OMP_CAPI(Player_EndTextDrawSelection, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerTextDrawData, data);
	data->endSelection();
}

OMP_CAPI(Player_SendClientCheck, void(objectPtr player, int actionType, int address, int offset, int count))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->sendClientCheck(actionType, address, offset, count);
}

OMP_CAPI(Player_Spawn, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->spawn();
}

OMP_CAPI(Player_GetSerial, void(objectPtr player, OutputStringViewPtr serial))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto result = player_->getSerial();
	SET_CAPI_STRING_VIEW(serial, result);
}

OMP_CAPI(Player_HasConsoleAccess, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_DATA_RET(player_, IPlayerConsoleData, data, false);
	return data->hasConsoleAccess();
}

OMP_CAPI(Player_Kick, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->kick();
}

OMP_CAPI(Player_SendGameText, void(objectPtr player, StringCharPtr text, int time, int style))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->sendGameText(text, Milliseconds(time), style);
}

OMP_CAPI(Player_HideGameText, void(objectPtr player, int style))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->hideGameText(style);
}

OMP_CAPI(Player_HasGameText, bool(objectPtr player, int style))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	bool has = player_->hasGameText(style);
	return has;
}

OMP_CAPI(Player_GetGameText, bool(objectPtr player, int style, OutputStringViewPtr message, int* time, int* remaining))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	Milliseconds mt;
	Milliseconds mr;
	StringView ms;
	if (player_->getGameText(style, ms, mt, mr))
	{
		COPY_STRING_TO_CAPI_STRING_VIEW(message, ms.data(), ms.size());
		*time = int(mt.count());
		*remaining = int(mr.count());
		return true;
	}
	return false;
}

OMP_CAPI(Player_Ban, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->ban();
}

OMP_CAPI(Player_BanEx, void(objectPtr player, StringCharPtr reason))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->ban(reason);
}

OMP_CAPI(Player_SendDeathMessage, void(objectPtr player, objectPtr killee, objectPtr killer, int weapon))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	ENTITY_CAST(IPlayer, killee, killee_);
	ENTITY_CAST(IPlayer, killer, killer_);
	player_->sendDeathMessage(*killee_, killer_, weapon);
}

OMP_CAPI(Player_SendEmptyDeathMessage, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->sendEmptyDeathMessage();
}

OMP_CAPI(Player_SendChatMessage, void(objectPtr player, objectPtr sender, StringCharPtr message))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	ENTITY_CAST(IPlayer, sender, sender_);
	player_->sendChatMessage(*sender_, message);
}

OMP_CAPI(Player_GetClientVersion, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	auto version = player_->getClientVersion();
	return int(version);
}

OMP_CAPI(Player_GetClientVersionName, void(objectPtr player, OutputStringViewPtr version))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto versionStr = player_->getClientVersionName();
	COPY_STRING_TO_CAPI_STRING_VIEW(version, versionStr.data(), versionStr.length());
}

OMP_CAPI(Player_GetSkillLevel, int(objectPtr player, int skill))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	auto skills = player_->getSkillLevels();
	if (skill >= 11 || skill < 0)
	{
		return 0;
	}
	int ret = skills[skill];
	return ret;
}

OMP_CAPI(Player_GetSurfingData, void(objectPtr player, int* type, int* id, float* offsetX, float* offsetY, float* offsetZ))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	const PlayerSurfingData& data = player_->getSurfingData();
	*type = int(data.type);
	*id = data.ID;
	*offsetX = data.offset.x;
	*offsetY = data.offset.y;
	*offsetZ = data.offset.z;
}

OMP_CAPI(Player_GetRotationQuat, void(objectPtr player, float* x, float* y, float* z, float* w))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	glm::quat rotQuat = player_->getRotation().q;

	// In samp or YSF, GetPlayerRotationQuat declaration is like this:
	// GetPlayerRotationQuat(playerid, &Float:w, &Float:x = 0.0, &Float:y = 0.0, &Float:z = 0.0);
	// Meaning first output arg is W and not X; Vector4's first member is X and it is used in many other places,
	// We can't just simply change ParamCast for Vector4 just because one function doesn't follow it.

	*x = rotQuat.w;
	*y = rotQuat.x;
	*z = rotQuat.y;
	*w = rotQuat.z;
}

OMP_CAPI(Player_GetSpectateData, void(objectPtr player, bool* spectating, int* spectateID, int* type))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	auto data = player_->getSpectateData();
	*spectating = data.spectating;
	*spectateID = data.spectateID;
	*type = data.type;
}

OMP_CAPI(Player_GetRawIp, uint32_t(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	uint32_t ip = player_->getNetworkData().networkID.address.v4;
	return ip;
}

OMP_CAPI(Player_SetGravity, void(objectPtr player, float gravity))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->setGravity(gravity);
}

OMP_CAPI(Player_GetGravity, float(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0.0f);
	float gravity = player_->getGravity();
	return gravity;
}

OMP_CAPI(Player_SetConsoleAccessibility, void(objectPtr player, bool set))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerConsoleData, data);
	data->setConsoleAccessibility(set);
}

OMP_CAPI(Player_IsSpawned, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PlayerState state = player_->getState();
	bool spawned = false;
	switch (state)
	{
	case PlayerState_OnFoot:
	case PlayerState_Driver:
	case PlayerState_Passenger:
	case PlayerState_Spawned:
	{
		spawned = true;
		break;
	}
	default:
		spawned = false;
	}
	return spawned;
}

OMP_CAPI(Player_GetControllable, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	bool controllable = bool(player_->getControllable());
	return controllable;
}

OMP_CAPI(Player_HasCameraTargetting, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	bool enabled = bool(player_->hasCameraTargeting());
	return enabled;
}

OMP_CAPI(Player_ToggleGhostMode, void(objectPtr player, bool toggle))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->toggleGhostMode(toggle);
}

OMP_CAPI(Player_IsGhostModeEnabled, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	return player_->isGhostModeEnabled();
}

OMP_CAPI(Player_AllowWeapons, void(objectPtr player, bool allow))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	player_->allowWeapons(allow);
}

OMP_CAPI(Player_AreWeaponsAllowed, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	bool allowed = bool(player_->areWeaponsAllowed());
	return allowed;
}

OMP_CAPI(Player_IsPlayerUsingOfficialClient, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	return player_->isUsingOfficialClient();
}

OMP_CAPI(Player_IsInDriveByMode, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_DATA_RET(player_, IPlayerVehicleData, data, false);
	return data->isInDriveByMode();
}

OMP_CAPI(Player_IsCuffed, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	bool cuffed = false;
	if (player_->getState() == PlayerState_OnFoot)
	{
		cuffed = bool(player_->getAction() == SpecialAction_Cuffed);
	}
	else if (player_->getState() == PlayerState_Passenger)
	{
		IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(player_);
		if (data)
		{
			cuffed = bool(data->isCuffed());
		}
	}
	return cuffed;
}

OMP_CAPI(Player_GetCustomSkin, uint32_t(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	PLAYER_DATA_RET(player_, IPlayerCustomModelsData, data, 0);
	return data->getCustomSkin();
}

OMP_CAPI(Player_GetMenu, objectPtr(objectPtr player))
{
	IMenusComponent* component = ComponentManager::Get()->menus;
	if (component)
	{
		POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
		IPlayerMenuData* menuData = queryExtension<IPlayerMenuData>(player_);
		if (menuData)
		{
			return component->get(menuData->getMenuID());
		}
	}
	return nullptr;
}

OMP_CAPI(Player_BeginEditingObject, void(objectPtr player, objectPtr object))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerObjectData, data);
	POOL_ENTITY(objects, IObject, object, object_);
	data->beginEditing(*object_);
}

OMP_CAPI(Player_BeginEditingPlayerObject, void(objectPtr player, objectPtr object))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerObjectData, data);
	PLAYER_POOL_ENTITY(player_, IPlayerObjectData, IPlayerObject, object, object_);
	data->beginEditing(*object_);
}

OMP_CAPI(Player_BeginSelectingObject, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerObjectData, data);
	data->beginSelecting();
}

OMP_CAPI(Player_EndEditingObject, void(objectPtr player))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_DATA(player_, IPlayerObjectData, data);
	data->endEditing();
}

OMP_CAPI(Player_RedirectDownload, bool(objectPtr player, StringCharPtr url))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_DATA_RET(player_, IPlayerCustomModelsData, data, false);

	if (!data->sendDownloadUrl(url))
	{
		ComponentManager::Get()->core->logLn(LogLevel::Warning, "This function can be used only within OnPlayerRequestDownload event.");
		return false;
	}
	return true;
}

OMP_CAPI(Player_GetCheckpoint, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	PLAYER_DATA_RET(player_, IPlayerCheckpointData, data, nullptr);
	ICheckpointData& cp = data->getCheckpoint();
	return &cp;
}

OMP_CAPI(Player_GetRaceCheckpoint, objectPtr(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	PLAYER_DATA_RET(player_, IPlayerCheckpointData, data, nullptr);
	IPlayerCheckpointData* playerData = queryExtension<IPlayerCheckpointData>(player_);
	IRaceCheckpointData& cp = playerData->getRaceCheckpoint();
	return &cp;
}
