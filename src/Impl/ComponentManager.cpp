/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, open.mp team and contributors.
 */

#include "Actors/Events.hpp"
#include "Checkpoints/Events.hpp"
#include "Classes/Events.hpp"
#include "Core/Events.hpp"
#include "Console/Events.hpp"
#include "Dialogs/Events.hpp"
#include "Menus/Events.hpp"
#include "Objects/Events.hpp"
#include "Pickups/Events.hpp"
#include "Players/Events.hpp"
#include "TextDraws/Events.hpp"
#include "Vehicles/Events.hpp"
#include "GangZones/Events.hpp"
#include "CustomModels/Events.hpp"
#include "ComponentManager.hpp"

#define ADD_EVENT_HANDLER(component, event_instance)                     \
	if (component)                                                       \
	{                                                                    \
		component->getEventDispatcher().addEventHandler(event_instance); \
	}

#define ADD_PLAYER_EVENT_HANDLER(component, event_name, event_instance)                 \
	if (component)                                                                      \
	{                                                                                   \
		component->getPlayer##event_name##Dispatcher().addEventHandler(event_instance); \
	}

#define REMOVE_EVENT_HANDLER(component, event_instance)                     \
	if (component)                                                          \
	{                                                                       \
		component->getEventDispatcher().removeEventHandler(event_instance); \
	}

#define REMOVE_PLAYER_EVENT_HANDLER(component, event_name, event_instance)                 \
	if (component)                                                                         \
	{                                                                                      \
		component->getPlayer##event_name##Dispatcher().removeEventHandler(event_instance); \
	}

#define RETRIEVE_RELEVANT_EVENT_MAP(container, priority)                        \
	FlatHashMap<Impl::String, FlatHashSet<EventCallback>>* container = nullptr; \
	switch (priority)                                                           \
	{                                                                           \
	case EventPriorityType_Highest:                                             \
		container = &highestPriorityEvents;                                     \
		break;                                                                  \
	case EventPriorityType_FairlyHigh:                                          \
		container = &fairlyHighPriorityEvents;                                  \
		break;                                                                  \
	case EventPriorityType_Default:                                             \
		container = &defaultPriorityEvents;                                     \
		break;                                                                  \
	case EventPriorityType_FairlyLow:                                           \
		container = &fairlyLowPriorityEvents;                                   \
		break;                                                                  \
	case EventPriorityType_Lowest:                                              \
		container = &lowestPriorityEvents;                                      \
		break;                                                                  \
	default:                                                                    \
		container = &defaultPriorityEvents;                                     \
		break;                                                                  \
	}

void ComponentManager::Init(ICore* c, IComponentList* clist)
{
	core = c;
	componentList = clist;
	players = &core->getPlayers();

	actors = GetComponent<IActorsComponent>();
	objects = GetComponent<IObjectsComponent>();
	pickups = GetComponent<IPickupsComponent>();
	textlabels = GetComponent<ITextLabelsComponent>();
	vehicles = GetComponent<IVehiclesComponent>();
	classes = GetComponent<IClassesComponent>();
	console = GetComponent<IConsoleComponent>();
	models = GetComponent<ICustomModelsComponent>();
	menus = GetComponent<IMenusComponent>();
	textdraws = GetComponent<ITextDrawsComponent>();
	gangzones = GetComponent<IGangZonesComponent>();
}

void ComponentManager::InitializeEvents()
{
	ADD_EVENT_HANDLER(core, CoreEvents::Get());
	ADD_EVENT_HANDLER(actors, ActorEvents::Get());
	ADD_EVENT_HANDLER(checkpoints, CheckpointEvents::Get());
	ADD_EVENT_HANDLER(classes, ClassEvents::Get());
	ADD_EVENT_HANDLER(dialogs, DialogEvents::Get());
	ADD_EVENT_HANDLER(menus, MenuEvents::Get());
	ADD_EVENT_HANDLER(textdraws, TextDrawEvents::Get());
	ADD_EVENT_HANDLER(pickups, PickupEvents::Get());
	ADD_EVENT_HANDLER(vehicles, VehicleEvents::Get());
	ADD_EVENT_HANDLER(objects, ObjectEvents::Get());
	ADD_EVENT_HANDLER(console, ConsoleEvents::Get());
	ADD_EVENT_HANDLER(gangzones, GangZoneEvents::Get());
	ADD_EVENT_HANDLER(models, CustomModelsEvents::Get());

	ADD_PLAYER_EVENT_HANDLER(players, Spawn, PlayerEvents::Get());
	ADD_PLAYER_EVENT_HANDLER(players, Connect, PlayerEvents::Get());
	ADD_PLAYER_EVENT_HANDLER(players, Stream, PlayerEvents::Get());
	ADD_PLAYER_EVENT_HANDLER(players, Text, PlayerEvents::Get());
	ADD_PLAYER_EVENT_HANDLER(players, Shot, PlayerEvents::Get());
	ADD_PLAYER_EVENT_HANDLER(players, Change, PlayerEvents::Get());
	ADD_PLAYER_EVENT_HANDLER(players, Damage, PlayerEvents::Get());
	ADD_PLAYER_EVENT_HANDLER(players, Click, PlayerEvents::Get());
	ADD_PLAYER_EVENT_HANDLER(players, Check, PlayerEvents::Get());
	ADD_PLAYER_EVENT_HANDLER(players, Update, PlayerEvents::Get());
}

void ComponentManager::FreeEvents()
{
	REMOVE_EVENT_HANDLER(core, CoreEvents::Get());
	REMOVE_EVENT_HANDLER(actors, ActorEvents::Get());
	REMOVE_EVENT_HANDLER(checkpoints, CheckpointEvents::Get());
	REMOVE_EVENT_HANDLER(classes, ClassEvents::Get());
	REMOVE_EVENT_HANDLER(dialogs, DialogEvents::Get());
	REMOVE_EVENT_HANDLER(menus, MenuEvents::Get());
	REMOVE_EVENT_HANDLER(textdraws, TextDrawEvents::Get());
	REMOVE_EVENT_HANDLER(pickups, PickupEvents::Get());
	REMOVE_EVENT_HANDLER(vehicles, VehicleEvents::Get());
	REMOVE_EVENT_HANDLER(objects, ObjectEvents::Get());
	REMOVE_EVENT_HANDLER(console, ConsoleEvents::Get());
	REMOVE_EVENT_HANDLER(gangzones, GangZoneEvents::Get());
	REMOVE_EVENT_HANDLER(models, CustomModelsEvents::Get());

	REMOVE_PLAYER_EVENT_HANDLER(players, Spawn, PlayerEvents::Get());
	REMOVE_PLAYER_EVENT_HANDLER(players, Connect, PlayerEvents::Get());
	REMOVE_PLAYER_EVENT_HANDLER(players, Stream, PlayerEvents::Get());
	REMOVE_PLAYER_EVENT_HANDLER(players, Text, PlayerEvents::Get());
	REMOVE_PLAYER_EVENT_HANDLER(players, Shot, PlayerEvents::Get());
	REMOVE_PLAYER_EVENT_HANDLER(players, Change, PlayerEvents::Get());
	REMOVE_PLAYER_EVENT_HANDLER(players, Damage, PlayerEvents::Get());
	REMOVE_PLAYER_EVENT_HANDLER(players, Click, PlayerEvents::Get());
	REMOVE_PLAYER_EVENT_HANDLER(players, Check, PlayerEvents::Get());
	REMOVE_PLAYER_EVENT_HANDLER(players, Update, PlayerEvents::Get());
}

bool ComponentManager::AddEventHandler(const Impl::String& name, EventPriorityType priority, EventCallback callback)
{
	if (name.length())
	{
		RETRIEVE_RELEVANT_EVENT_MAP(container, priority);
		if (container)
		{
			auto it = container->find(name);
			if (it == container->end())
			{
				it = container->insert({ name, FlatHashSet<EventCallback>() }).first;
			}

			it->second.insert(callback);
			return true;
		}
	}
	return false;
}

bool ComponentManager::RemoveEventHandler(const Impl::String& name, EventPriorityType priority, EventCallback callback)
{
	if (name.length())
	{
		RETRIEVE_RELEVANT_EVENT_MAP(container, priority);
		if (container)
		{
			auto it = container->find(name);
			if (it != container->end())
			{
				it->second.erase(callback);
				return true;
			}
		}
	}
	return false;
}

void ComponentManager::RemoveAllHandlers(const Impl::String& name, EventPriorityType priority)
{
	if (name.length())
	{
		RETRIEVE_RELEVANT_EVENT_MAP(container, priority);
		if (container)
		{
			container->erase(name);
		}
	}
}
