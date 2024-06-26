/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, open.mp team and contributors.
 */

#pragma once
#include "../ComponentManager.hpp"
#include "../../Utils/Singleton.hpp"
#include "sdk.hpp"

struct TextDrawEvents : public TextDrawEventHandler, public Singleton<TextDrawEvents>
{
	virtual bool onPlayerCancelTextDrawSelection(IPlayer& player) override
	{
		ComponentManager::Get()->CallEvent("onPlayerCancelTextDrawSelection", EventReturnHandler::None, &player);
		return true;
	}

	virtual bool onPlayerCancelPlayerTextDrawSelection(IPlayer& player) override
	{
		ComponentManager::Get()->CallEvent("onPlayerCancelPlayerTextDrawSelection", EventReturnHandler::None, &player);
		return true;
	}

	void onPlayerClickTextDraw(IPlayer& player, ITextDraw& td) override
	{
		ComponentManager::Get()->CallEvent("onPlayerClickTextDraw", EventReturnHandler::None, &player, &td);
	}

	void onPlayerClickPlayerTextDraw(IPlayer& player, IPlayerTextDraw& td) override
	{
		ComponentManager::Get()->CallEvent("onPlayerClickPlayerTextDraw", EventReturnHandler::None, &player, &td);
	}
};
