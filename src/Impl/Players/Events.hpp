/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, open.mp team and contributors.
 */

#pragma once
#include "../ComponentManager.hpp"
#include "../Utils/Singleton.hpp"
#include "sdk.hpp"

class PlayerEvents : public PlayerSpawnEventHandler, public PlayerConnectEventHandler, public PlayerStreamEventHandler, public PlayerTextEventHandler, public PlayerShotEventHandler, public PlayerChangeEventHandler, public PlayerDamageEventHandler, public PlayerClickEventHandler, public PlayerCheckEventHandler, public PlayerUpdateEventHandler, public Singleton<PlayerEvents>
{
public:
	void onPlayerConnect(IPlayer& player) override
	{
		ComponentManager::Get()->CallEvent("onPlayerConnect", EventReturnHandler::None, &player);
	}

	void onPlayerSpawn(IPlayer& player) override
	{
		ComponentManager::Get()->CallEvent("onPlayerSpawn", EventReturnHandler::None, &player);
	}

	bool onPlayerCommandText(IPlayer& player, StringView cmdtext) override
	{
		return ComponentManager::Get()->CallEvent("onPlayerCommandText", EventReturnHandler::StopAtTrue, &player, CREATE_CAPI_STRING_VIEW(cmdtext));
	}

	void onPlayerKeyStateChange(IPlayer& player, uint32_t newKeys, uint32_t oldKeys) override
	{
		ComponentManager::Get()->CallEvent("onPlayerKeyStateChange", EventReturnHandler::None, &player, int(newKeys), int(oldKeys));
	}

	void onIncomingConnection(IPlayer& player, StringView ipAddress, unsigned short port) override
	{
		ComponentManager::Get()->CallEvent("onIncomingConnection", EventReturnHandler::None, &player, CREATE_CAPI_STRING_VIEW(ipAddress), int(port));
	}

	void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override
	{
		ComponentManager::Get()->CallEvent("onPlayerDisconnect", EventReturnHandler::None, &player, int(reason));
	}

	bool onPlayerRequestSpawn(IPlayer& player) override
	{
		return ComponentManager::Get()->CallEvent("onPlayerRequestSpawn", EventReturnHandler::StopAtFalse, &player);
	}

	void onPlayerStreamIn(IPlayer& player, IPlayer& forPlayer) override
	{
		ComponentManager::Get()->CallEvent("onPlayerStreamIn", EventReturnHandler::None, &player, &forPlayer);
	}

	void onPlayerStreamOut(IPlayer& player, IPlayer& forPlayer) override
	{
		ComponentManager::Get()->CallEvent("onPlayerStreamOut", EventReturnHandler::None, &player, &forPlayer);
	}

	bool onPlayerText(IPlayer& player, StringView message) override
	{
		return ComponentManager::Get()->CallEvent("onPlayerText", EventReturnHandler::StopAtFalse, &player, CREATE_CAPI_STRING_VIEW(message));
	}

	bool onPlayerShotMissed(IPlayer& player, const PlayerBulletData& bulletData) override
	{
		return ComponentManager::Get()->CallEvent("onPlayerShotMissed", EventReturnHandler::StopAtFalse, &player,
			int(bulletData.weapon), bulletData.offset.x, bulletData.offset.y, bulletData.offset.z);
	}

	bool onPlayerShotPlayer(IPlayer& player, IPlayer& target, const PlayerBulletData& bulletData) override
	{
		return ComponentManager::Get()->CallEvent("onPlayerShotPlayer", EventReturnHandler::StopAtFalse, &player, &target,
			int(bulletData.weapon), bulletData.offset.x, bulletData.offset.y, bulletData.offset.z);
	}

	bool onPlayerShotVehicle(IPlayer& player, IVehicle& target, const PlayerBulletData& bulletData) override
	{
		return ComponentManager::Get()->CallEvent("onPlayerShotVehicle", EventReturnHandler::StopAtFalse, &player, &target,
			int(bulletData.weapon), bulletData.offset.x, bulletData.offset.y, bulletData.offset.z);
	}

	bool onPlayerShotObject(IPlayer& player, IObject& target, const PlayerBulletData& bulletData) override
	{
		return ComponentManager::Get()->CallEvent("onPlayerShotObject", EventReturnHandler::StopAtFalse, &player, &target,
			int(bulletData.weapon), bulletData.offset.x, bulletData.offset.y, bulletData.offset.z);
	}

	bool onPlayerShotPlayerObject(IPlayer& player, IPlayerObject& target, const PlayerBulletData& bulletData) override
	{
		return ComponentManager::Get()->CallEvent("onPlayerShotPlayerObject", EventReturnHandler::StopAtFalse, &player, &target,
			int(bulletData.weapon), bulletData.offset.x, bulletData.offset.y, bulletData.offset.z);
	}

	void onPlayerDeath(IPlayer& player, IPlayer* killer, int reason) override
	{
		ComponentManager::Get()->CallEvent("onPlayerDeath", EventReturnHandler::None, &player, killer, reason);
	}

	void onPlayerTakeDamage(IPlayer& player, IPlayer* from, float amount, unsigned weapon, BodyPart part) override
	{
		ComponentManager::Get()->CallEvent("onPlayerTakeDamage", EventReturnHandler::None, &player, from, amount, int(weapon), int(part));
	}

	void onPlayerGiveDamage(IPlayer& player, IPlayer& to, float amount, unsigned weapon, BodyPart part) override
	{
		ComponentManager::Get()->CallEvent("onPlayerGiveDamage", EventReturnHandler::None, &player, &to, amount, int(weapon), int(part));
	}

	void onPlayerInteriorChange(IPlayer& player, unsigned newInterior, unsigned oldInterior) override
	{
		ComponentManager::Get()->CallEvent("onPlayerInteriorChange", EventReturnHandler::None, &player, int(newInterior), int(oldInterior));
	}

	void onPlayerStateChange(IPlayer& player, PlayerState newState, PlayerState oldState) override
	{
		ComponentManager::Get()->CallEvent("onPlayerStateChange", EventReturnHandler::None, &player, int(newState), int(oldState));
	}

	void onPlayerClickMap(IPlayer& player, Vector3 pos) override
	{
		ComponentManager::Get()->CallEvent("onPlayerClickMap", EventReturnHandler::None, &player, pos.x, pos.y, pos.z);
	}

	void onPlayerClickPlayer(IPlayer& player, IPlayer& clicked, PlayerClickSource source) override
	{
		ComponentManager::Get()->CallEvent("onPlayerClickPlayer", EventReturnHandler::None, &player, &clicked, int(source));
	}

	void onClientCheckResponse(IPlayer& player, int actionType, int address, int results) override
	{
		ComponentManager::Get()->CallEvent("onClientCheckResponse", EventReturnHandler::None, &player, actionType, address, results);
	}

	bool onPlayerUpdate(IPlayer& player, TimePoint now) override
	{
		return ComponentManager::Get()->CallEvent("onPlayerUpdate", EventReturnHandler::StopAtFalse, &player);
	}
};
