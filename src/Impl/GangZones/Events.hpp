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

struct GangZoneEvents : public GangZoneEventHandler, public Singleton<GangZoneEvents>
{
	void onPlayerEnterGangZone(IPlayer& player, IGangZone& zone) override
	{
		auto gangzones = ComponentManager::Get()->gangzones;
		if (zone.getLegacyPlayer() == nullptr)
		{
			ComponentManager::Get()->CallEvent("onPlayerEnterGangZone", EventReturnHandler::None, &player, &zone);
		}
		else if (auto data = queryExtension<IPlayerGangZoneData>(player))
		{
		}
	}

	void onPlayerLeaveGangZone(IPlayer& player, IGangZone& zone) override
	{
		auto gangzones = ComponentManager::Get()->gangzones;
		if (zone.getLegacyPlayer() == nullptr)
		{
			ComponentManager::Get()->CallEvent("onPlayerLeaveGangZone", EventReturnHandler::None, &player, &zone);
		}
		else if (auto data = queryExtension<IPlayerGangZoneData>(player))
		{
		}
	}

	void onPlayerClickGangZone(IPlayer& player, IGangZone& zone) override
	{
		auto gangzones = ComponentManager::Get()->gangzones;
		if (zone.getLegacyPlayer() == nullptr)
		{
			ComponentManager::Get()->CallEvent("onPlayerClickGangZone", EventReturnHandler::None, &player, &zone);
		}
		else if (auto data = queryExtension<IPlayerGangZoneData>(player))
		{
		}
	}
};
