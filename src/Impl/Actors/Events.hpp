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

struct ActorEvents : public ActorEventHandler, public Singleton<ActorEvents>
{
	void onPlayerGiveDamageActor(IPlayer& player, IActor& actor, float amount, unsigned weapon, BodyPart part) override
	{
		ComponentManager::Get()->CallEvent("Actor_OnPlayerGiveDamage", player.getID(), actor.getID(), amount, weapon, int(part));
	}

	void onActorStreamIn(IActor& actor, IPlayer& forPlayer) override
	{
		ComponentManager::Get()->CallEvent("Actor_OnStreamIn", actor.getID(), forPlayer.getID());
	}

	void onActorStreamOut(IActor& actor, IPlayer& forPlayer) override
	{
		ComponentManager::Get()->CallEvent("Actor_OnStreamOut", actor.getID(), forPlayer.getID());
	}
};
