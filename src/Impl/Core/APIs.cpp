/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, open.mp team and contributors.
 */

#include "../ComponentManager.hpp"
#include <sstream>
#include <iomanip>

OMP_CAPI(Core_TickCount, int())
{
	auto tick = ComponentManager::Get()->core->getTickCount();
	return tick;
}

OMP_CAPI(Core_MaxPlayers, int())
{
	int max = *ComponentManager::Get()->core->getConfig().getInt("max_players");
	return max;
}

OMP_CAPI(Core_Log, void(StringCharPtr text))
{
	ComponentManager::Get()->core->printLn("%s", text);
}

OMP_CAPI(Core_IsAdminTeleportAllowed, bool())
{
	bool allowed = *ComponentManager::Get()->core->getConfig().getBool("rcon.allow_teleport");
	return allowed;
}

OMP_CAPI(Core_AllowAdminTeleport, void(bool allow))
{
	*ComponentManager::Get()->core->getConfig().getBool("rcon.allow_teleport") = allow;
}

OMP_CAPI(Core_AreAllAnimationsEnabled, bool())
{
	bool allowed = *ComponentManager::Get()->core->getConfig().getBool("game.use_all_animations");
	return allowed;
}

OMP_CAPI(Core_EnableAllAnimations, void(bool allow))
{
	*ComponentManager::Get()->core->getConfig().getBool("game.use_all_animations") = allow;
}

OMP_CAPI(Core_IsAnimationLibraryValid, bool(StringCharPtr name))
{
	auto valid = animationLibraryValid(name, true);
	return valid;
}

OMP_CAPI(Core_AreInteriorWeaponsAllowed, bool())
{
	bool allowed = *ComponentManager::Get()->core->getConfig().getBool("game.allow_interior_weapons");
	return allowed;
}

OMP_CAPI(Core_AllowInteriorWeapons, void(bool allow))
{
	if (allow)
	{
		*ComponentManager::Get()->core->getConfig().getBool("game.allow_interior_weapons") = true;
	}
	else
	{
		IPlayerPool* players = ComponentManager::Get()->players;
		for (IPlayer* player : players->entries())
		{
			if (player->getInterior() && player->areWeaponsAllowed())
			{
				// Because they are allowed weapons currently this will send a full client reset.
				player->resetWeapons();
			}
		}
		// By the time the player reports having no weapons, this is set and so we remember the old
		// ones still.
		*ComponentManager::Get()->core->getConfig().getBool("game.allow_interior_weapons") = false;
	}
}

OMP_CAPI(Core_BlockIpAddress, bool(StringCharPtr ipAddress, int timeMS))
{
	if (strlen(ipAddress) < 1)
	{
		return false;
	}
	BanEntry entry(ipAddress);
	for (INetwork* network : ComponentManager::Get()->core->getNetworks())
	{
		network->ban(entry, Milliseconds(timeMS));
	}
	return true;
}

OMP_CAPI(Core_UnBlockIpAddress, void(StringCharPtr ipAddress))
{
	BanEntry entry(ipAddress);
	for (INetwork* network : ComponentManager::Get()->core->getNetworks())
	{
		network->unban(entry);
	}
}

OMP_CAPI(NPC_Connect, void(StringCharPtr name, StringCharPtr script))
{
	ComponentManager::Get()->core->connectBot(name, script);
}

OMP_CAPI(Core_DisableEntryExitMarkers, void())
{
	*ComponentManager::Get()->core->getConfig().getBool("game.use_entry_exit_markers") = false;
}

OMP_CAPI(Core_DisableNameTagsLOS, void())
{
	*ComponentManager::Get()->core->getConfig().getBool("game.use_nametag_los") = false;
}

OMP_CAPI(Core_EnableZoneNames, void(bool enable))
{
	*ComponentManager::Get()->core->getConfig().getBool("game.use_zone_names") = enable;
}

OMP_CAPI(Core_ShowGameTextForAll, bool(StringCharPtr msg, int time, int style))
{
	if (strlen(msg) < 1)
	{
		return false;
	}
	ComponentManager::Get()->players->sendGameTextToAll(msg, Milliseconds(time), style);
	return true;
}

OMP_CAPI(Core_HideGameTextForAll, void(int style))
{
	ComponentManager::Get()->players->hideGameTextForAll(style);
}

OMP_CAPI(Core_NetworkStats, int(OutputStringViewPtr output))
{
	std::stringstream stream;
	NetworkStats stats;

	for (INetwork* network : ComponentManager::Get()->core->getNetworks())
	{
		if (network->getNetworkType() == ENetworkType::ENetworkType_RakNetLegacy)
		{
			stats = network->getStatistics();
		}
	}

	stream
		<< "Server Ticks: " << ComponentManager::Get()->core->tickRate() << std::endl
		<< "Messages in Send buffer: " << stats.messageSendBuffer << std::endl
		<< "Messages sent: " << stats.messagesSent << std::endl
		<< "Bytes sent: " << stats.totalBytesSent << std::endl
		<< "Acks sent: " << stats.acknowlegementsSent << std::endl
		<< "Acks in send buffer: " << stats.acknowlegementsPending << std::endl
		<< "Messages waiting for ack: " << stats.messagesOnResendQueue << std::endl
		<< "Messages resent: " << stats.messageResends << std::endl
		<< "Bytes resent: " << stats.messagesTotalBytesResent << std::endl
		<< "Packetloss: " << std::setprecision(1) << std::fixed << stats.packetloss << "%" << std::endl
		<< "Messages received: " << stats.messagesReceived << std::endl
		<< "Bytes received: " << stats.bytesReceived << std::endl
		<< "Acks received: " << stats.acknowlegementsReceived << std::endl
		<< "Duplicate acks received: " << stats.duplicateAcknowlegementsReceived << std::endl
		<< "Inst. KBits per second: " << std::setprecision(1) << (stats.bitsPerSecond / 1000.0) << std::endl
		<< "KBits per second sent: " << std::setprecision(1) << (stats.bpsSent / 1000.0) << std::endl
		<< "KBits per second received: " << std::setprecision(1) << (stats.bpsReceived / 1000.0) << std::endl;

	int len = stream.str().size();
	COPY_STRING_TO_CAPI_STRING_VIEW(output, stream.str().c_str(), len);
	return len;
}

OMP_CAPI(Player_GetNetworkStats, int(objectPtr player, OutputStringViewPtr output))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	std::stringstream stream;
	NetworkStats stats = player_->getNetworkData().network->getStatistics(player_);

	stream
		<< "Network Active: " << int(stats.isActive) << std::endl
		<< "Network State: " << stats.connectMode << std::endl
		<< "Messages in Send buffer: " << stats.messageSendBuffer << std::endl
		<< "Messages sent: " << stats.messagesSent << std::endl
		<< "Bytes sent: " << stats.totalBytesSent << std::endl
		<< "Acks sent: " << stats.acknowlegementsSent << std::endl
		<< "Acks in send buffer: " << stats.acknowlegementsPending << std::endl
		<< "Messages waiting for ack: " << stats.messagesOnResendQueue << std::endl
		<< "Messages resent: " << stats.messageResends << std::endl
		<< "Bytes resent: " << stats.messagesTotalBytesResent << std::endl
		<< "Packetloss: " << std::setprecision(1) << std::fixed << stats.packetloss << "%" << std::endl
		<< "Messages received: " << stats.messagesReceived << std::endl
		<< "Bytes received: " << stats.bytesReceived << std::endl
		<< "Acks received: " << stats.acknowlegementsReceived << std::endl
		<< "Duplicate acks received: " << stats.duplicateAcknowlegementsReceived << std::endl
		<< "Inst. KBits per second: " << std::setprecision(1) << (stats.bitsPerSecond / 1000.0) << std::endl
		<< "KBits per second sent: " << std::setprecision(1) << (stats.bpsSent / 1000.0) << std::endl
		<< "KBits per second received: " << std::setprecision(1) << (stats.bpsReceived / 1000.0) << std::endl;

	int len = stream.str().size();
	COPY_STRING_TO_CAPI_STRING_VIEW(output, stream.str().c_str(), len);
	return len;
}

OMP_CAPI(Core_ServerTickRate, int())
{
	int tick = ComponentManager::Get()->core->tickRate();
	return tick;
}

OMP_CAPI(Core_GetWeaponName, bool(int weaponid, OutputStringViewPtr output))
{
	SET_CAPI_STRING_VIEW(output, ComponentManager::Get()->core->getWeaponName(PlayerWeapon(weaponid)));
	return true;
}

OMP_CAPI(Core_SetChatRadius, void(float globalChatRadius))
{
	*ComponentManager::Get()->core->getConfig().getBool("game.use_chat_radius") = true;
	*ComponentManager::Get()->core->getConfig().getFloat("game.chat_radius") = globalChatRadius;
}

OMP_CAPI(Core_SetMarkerRadius, void(float playerMarkerRadius))
{
	*ComponentManager::Get()->core->getConfig().getBool("game.use_player_marker_draw_radius") = true;
	*ComponentManager::Get()->core->getConfig().getFloat("game.player_marker_draw_radius") = playerMarkerRadius;
}

OMP_CAPI(Player_NetStatsBytesReceived, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(player_);
	int bytes = stats.bytesReceived;
	return bytes;
}

OMP_CAPI(Player_NetStatsBytesSent, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(player_);
	int bytes = stats.totalBytesSent;
	return bytes;
}

OMP_CAPI(Player_NetStatsConnectionStatus, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(player_);
	int status = stats.connectMode;
	return status;
}

OMP_CAPI(Player_NetStatsGetConnectedTime, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(player_);
	int ms = stats.connectionElapsedTime;
	return ms;
}

OMP_CAPI(Player_NetStatsGetIpPort, bool(objectPtr player, OutputStringViewPtr output))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PeerNetworkData data = player_->getNetworkData();
	PeerAddress::AddressString addressString;
	if (PeerAddress::ToString(data.networkID.address, addressString))
	{
		Impl::String ip_port((StringView(addressString)));
		ip_port += ":";
		ip_port += std::to_string(data.networkID.port);
		int len = ip_port.length();
		COPY_STRING_TO_CAPI_STRING_VIEW(output, ip_port.c_str(), len);
		return len;
	}
	return 0;
}

OMP_CAPI(Player_NetStatsMessagesReceived, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(player_);
	int received = stats.messagesReceived;
	return received;
}

OMP_CAPI(Player_NetStatsMessagesRecvPerSecond, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(player_);
	int received = stats.messagesReceivedPerSecond;
	return received;
}

OMP_CAPI(Player_NetStatsMessagesSent, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(player_);
	int sent = stats.messagesSent;
	return sent;
}

OMP_CAPI(Player_NetStatsPacketLossPercent, float(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0.0f);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(player_);
	auto packetLoss = stats.packetloss;
	return packetLoss;
}

OMP_CAPI(Core_SendRconCommand, void(StringCharPtr command))
{
	IConsoleComponent* console = ComponentManager::Get()->console;
	if (console)
	{
		console->send(command);
	}
}

OMP_CAPI(Core_SetDeathDropAmount, void(int amount))
{
	*ComponentManager::Get()->core->getConfig().getInt("game.death_drop_amount") = amount;
}

OMP_CAPI(Core_GameMode_SetText, void(StringCharPtr string))
{
	ComponentManager::Get()->core->setData(SettableCoreDataType::ModeText, string);
}

OMP_CAPI(Core_SetGravity, void(float gravity))
{
	ComponentManager::Get()->core->setGravity(gravity);
}

OMP_CAPI(Core_GetGravity, float())
{
	float gravity = ComponentManager::Get()->core->getGravity();
	return gravity;
}

OMP_CAPI(Core_SetNameTagsDrawDistance, void(float distance))
{
	*ComponentManager::Get()->core->getConfig().getFloat("game.nametag_draw_radius") = distance;
}

OMP_CAPI(Core_SetWeather, void(int weatherid))
{
	ComponentManager::Get()->core->setWeather(weatherid);
}

OMP_CAPI(Core_SetWorldTime, void(int hour))
{
	ComponentManager::Get()->core->setWorldTime(Hours(hour));
}

OMP_CAPI(Core_ShowNameTags, void(bool show))
{
	*ComponentManager::Get()->core->getConfig().getBool("game.use_nametags") = show;
}

OMP_CAPI(Core_ShowPlayerMarkers, void(int mode))
{
	*ComponentManager::Get()->core->getConfig().getInt("game.player_marker_mode") = mode;
}

OMP_CAPI(Core_UsePedAnims, void())
{
	*ComponentManager::Get()->core->getConfig().getBool("game.use_player_ped_anims") = true;
}

OMP_CAPI(Core_GetWeather, int())
{
	int weather = *ComponentManager::Get()->core->getConfig().getInt("game.weather");
	return weather;
}

OMP_CAPI(Core_GetWorldTime, int())
{
	int hour = *ComponentManager::Get()->core->getConfig().getInt("game.time");
	return hour;
}

OMP_CAPI(Core_ToggleChatTextReplacement, void(bool enable))
{
	*ComponentManager::Get()->core->getConfig().getBool("chat_input_filter") = enable;
}

OMP_CAPI(Core_IsChatTextReplacementToggled, bool())
{
	bool toggled = *ComponentManager::Get()->core->getConfig().getBool("chat_input_filter");
	return toggled;
}

OMP_CAPI(Core_IsNickNameValid, bool(StringCharPtr name))
{
	auto valid = ComponentManager::Get()->players->isNameValid(name);
	return valid;
}

OMP_CAPI(Core_AllowNickNameCharacter, void(int character, bool allow))
{
	ComponentManager::Get()->players->allowNickNameCharacter(character, allow);
}

OMP_CAPI(Core_IsNickNameCharacterAllowed, bool(int character))
{
	bool allowed = ComponentManager::Get()->players->isNickNameCharacterAllowed(character);
	return allowed;
}

OMP_CAPI(Core_ClearBanList, void())
{
	ICore* core = ComponentManager::Get()->core;
	if (!core)
	{
		return;
	}

	core->getConfig().clearBans();
}

OMP_CAPI(Core_IsIpAddressBanned, bool(StringCharPtr ip))
{
	ICore* core = ComponentManager::Get()->core;
	if (!core)
	{
		return false;
	}
	BanEntry entry(ip);
	bool isBanned = core->getConfig().isBanned(entry);
	return isBanned;
}

OMP_CAPI(Core_GetWeaponSlot, int(uint8_t weapon))
{
	int slot = WeaponSlotData { weapon }.slot();
	return slot;
}

OMP_CAPI(Core_AddRule, bool(StringCharPtr name, StringCharPtr value))
{
	ICore* core = ComponentManager::Get()->core;
	if (!core)
	{
		return false;
	}

	for (INetwork* network : core->getNetworks())
	{
		INetworkQueryExtension* query = queryExtension<INetworkQueryExtension>(network);

		if (query)
		{
			query->addRule(name, value);
			return true;
		}
	}
	return false;
}

OMP_CAPI(Core_IsValidRule, bool(StringCharPtr name))
{
	ICore* core = ComponentManager::Get()->core;
	if (!core)
	{
		return false;
	}

	for (INetwork* network : core->getNetworks())
	{
		INetworkQueryExtension* query = queryExtension<INetworkQueryExtension>(network);

		if (query)
		{
			bool valid = query->isValidRule(name);
			return valid;
		}
	}
	return false;
}

OMP_CAPI(Core_RemoveRule, bool(StringCharPtr name))
{
	ICore* core = ComponentManager::Get()->core;
	if (!core)
	{
		return false;
	}

	for (INetwork* network : core->getNetworks())
	{
		INetworkQueryExtension* query = queryExtension<INetworkQueryExtension>(network);

		if (query)
		{
			query->removeRule(name);
			return true;
		}
	}
	return false;
}
