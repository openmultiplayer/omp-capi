/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, open.mp team and contributors.
 */

#pragma once
#include <variant>

#include "../Utils/Singleton.hpp"
#include "../Utils/MacroMagic.hpp"
#include "../../include/types.h"

#include "sdk.hpp"
#include "Server/Components/Pickups/pickups.hpp"
#include "Server/Components/Objects/objects.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "Server/Components/Actors/actors.hpp"
#include "Server/Components/Classes/classes.hpp"
#include "Server/Components/Console/console.hpp"
#include "Server/Components/CustomModels/custommodels.hpp"
#include "Server/Components/Dialogs/dialogs.hpp"
#include "Server/Components/Menus/menus.hpp"
#include "Server/Components/TextDraws/textdraws.hpp"
#include "Server/Components/Recordings/recordings.hpp"
#include "Server/Components/TextDraws/textdraws.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"
#include "Server/Components/GangZones/gangzones.hpp"

class ComponentManager : public Singleton<ComponentManager>
{
public:
	ICore* core = nullptr;
	IPlayerPool* players = nullptr;
	IPickupsComponent* pickups = nullptr;
	IObjectsComponent* objects = nullptr;
	ITextLabelsComponent* textlabels = nullptr;
	IVehiclesComponent* vehicles = nullptr;
	IActorsComponent* actors = nullptr;
	IClassesComponent* classes = nullptr;
	IConsoleComponent* console = nullptr;
	ICustomModelsComponent* models = nullptr;
	IMenusComponent* menus = nullptr;
	ITextDrawsComponent* textdraws = nullptr;
	IGangZonesComponent* gangzones = nullptr;
	ICheckpointsComponent* checkpoints = nullptr;
	IDialogsComponent* dialogs = nullptr;

	/// Store open.mp components
	void Init(ICore* c, IComponentList* clist);

	// Add event handlers to components' event dispatchers
	void InitializeEvents();

	// Remove event handlers from components' event dispatchers
	void FreeEvents();

	// Add an event callback of an event to omp capi handler maps
	void AddEvent(const Impl::String& name, EventPriorityType priority, EventCallback callback);

	// Remove an event callback of an event from omp capi handler maps
	void RemoveEvent(const Impl::String& name, EventPriorityType priority, EventCallback callback);

	// Remove all event callbacks of an event
	void RemoveAll(const Impl::String& name, EventPriorityType priority);

	/// Get open.mp core instance
	ICore* GetCore()
	{
		return core;
	}

	/// Get an open.mp component
	template <typename ComponentType>
	ComponentType* GetComponent()
	{
		return componentList->queryComponent<ComponentType>();
	}

	// Call event
	template <typename... Args>
	bool CallEvent(const Impl::String& name, Args...)
	{
		auto highest = highestPriorityEvents.find(name);
		auto high = highPriorityEvents.find(name);
		auto default = defaultPriorityEvents.find(name);
		auto low = lowPriorityEvents.find(name);
		auto lowest = lowestPriorityEvents.find(name);

		bool result = true;

		if (highest != highestPriorityEvents.end())
		{
			auto ret = CallEventOfPriority(highest);
			if (!ret)
			{
				result = false;
			}
		}

		if (high != highPriorityEvents.end())
		{
			auto ret = CallEventOfPriority(highest);
			if (!ret)
			{
				result = false;
			}
		}

		if (default != defaultPriorityEvents.end())
		{
			auto ret = CallEventOfPriority(highest);
			if (!ret)
			{
				result = false;
			}
		}

		if (low != lowPriorityEvents.end())
		{
			auto ret = CallEventOfPriority(highest);
			if (!ret)
			{
				result = false;
			}
		}

		if (lowest != lowestPriorityEvents.end())
		{
			auto ret = CallEventOfPriority(highest);
			if (!ret)
			{
				result = false;
			}
		}

		return result;
	}

private:
	IComponentList* componentList = nullptr;

	FlatHashMap<Impl::String, FlatHashSet<EventCallback>> highestPriorityEvents;
	FlatHashMap<Impl::String, FlatHashSet<EventCallback>> fairlyHighPriorityEvents;
	FlatHashMap<Impl::String, FlatHashSet<EventCallback>> defaultPriorityEvents;
	FlatHashMap<Impl::String, FlatHashSet<EventCallback>> fairlyLowPriorityEvents;
	FlatHashMap<Impl::String, FlatHashSet<EventCallback>> lowestPriorityEvents;

	template <typename Con, typename... Args>
	bool CallEventOfPriority(Con container, Args...)
	{
		EventArgs eventArgs;
		constexpr std::size_t size = sizeof...(Args);
		void* args[size] = {... 0 };

		eventArgs.data = &args;
		eventArgs.size = size;
		bool result = true;
		for (auto cb : container->second)
		{
			if (cb)
			{
				int i = 0;
				([&]
					{
						eventArgs.data[i] = &inputs;
						i++;
					}(),
					...);

				auto ret = cb(&eventArgs);
				if (!ret)
				{
					result = false;
				}
			}
		}

		return result;
	}
};

/// Get player from players pool
template <typename PlayerDataType>
inline PlayerDataType* GetPlayerData(IPlayer* player)
{
	if (player == nullptr)
	{
		return nullptr;
	}
	return queryExtension<PlayerDataType>(*player);
}

/// Cast object pointer to entity type, return fail_ret if not available
#define ENTITY_CAST_RET(entity_type, entity, output, failret) \
	if (!entity)                                              \
		return failret;                                       \
	entity_type* output = reinterpret_cast<entity_type*>(entity)

#define ENTITY_CAST(entity_type, entity, output) \
	if (!entity)                                 \
		return;                                  \
	entity_type* output = reinterpret_cast<entity_type*>(entity)

#define POOL_ENTITY_RET(pool, entity_type, entity, output, failret) \
	if (!ComponentManager::Get()->pool)                             \
		return failret;                                             \
	auto pool = ComponentManager::Get()->pool;                      \
	ENTITY_CAST_RET(entity_type, entity, output, failret);

#define POOL_ENTITY(pool, entity_type, entity, output) \
	if (!ComponentManager::Get()->pool)                \
		return;                                        \
	auto pool = ComponentManager::Get()->pool;         \
	ENTITY_CAST(entity_type, entity, output);

#define PLAYER_POOL_ENTITY_RET(player, pool_type, entity_type, entity, entity_output, failret) \
	auto playerData = GetPlayerData<pool_type>(player);                                        \
	if (playerData == nullptr)                                                                 \
		return failret;                                                                        \
	entity_type* entity_output = reinterpret_cast<entity_type*>(entity);                       \
	if (entity_output == nullptr)                                                              \
		return failret;

#define PLAYER_DATA_RET(player, entity_type, entity_output, failret) \
	auto entity_output = GetPlayerData<entity_type>(player);         \
	if (entity_output == nullptr)                                    \
	return failret

#define COPY_STRING_TO_CAPI_STRING_VIEW(output, src, len_) \
	if (output)                                            \
	{                                                      \
		output->len = len_;                                \
		memcpy(output->data, src, len_);                   \
	}

#define SET_CAPI_STRING_VIEW(output, str_view)             \
	if (output)                                            \
	{                                                      \
		output->len = str_view.length();                   \
		output->data = const_cast<char*>(str_view.data()); \
	}

#define CREATE_CAPI_STRING_VIEW(str) \
	CAPIStringView { static_cast<unsigned int>(str.length()), const_cast<char*>(str.data()) }
