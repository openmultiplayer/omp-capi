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

struct CheckpointEvents : public PlayerCheckpointEventHandler, public Singleton<CheckpointEvents>
{
	void onPlayerEnterCheckpoint(IPlayer& player) override
	{
		ComponentManager::Get()->CallEvent("Player_OnEnterCheckpoint", player.getID());
	}

	void onPlayerLeaveCheckpoint(IPlayer& player) override
	{
		ComponentManager::Get()->CallEvent("Player_OnLeaveCheckpoint", player.getID());
	}

	void onPlayerEnterRaceCheckpoint(IPlayer& player) override
	{
		ComponentManager::Get()->CallEvent("Player_OnEnterRaceCheckpoint", player.getID());
	}

	void onPlayerLeaveRaceCheckpoint(IPlayer& player) override
	{

		ComponentManager::Get()->CallEvent("Player_OnLeaveRaceCheckpoint", player.getID());
	}
};
