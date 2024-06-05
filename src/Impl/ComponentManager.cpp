#include "ComponentManager.hpp"

#define ADD_EVENT_HANDLER(component, event_instance) \
	if (component) \
	{ \
		component->getEventDispatcher().addEventHandler(event_instance); \
	}

#define ADD_PLAYER_EVENT_HANDLER(component, event_name, event_instance) \
	if (component) \
	{ \
		component->getPlayer##event_name##Dispatcher().addEventHandler(event_instance); \
	}

#define REMOVE_EVENT_HANDLER(component, event_instance) \
	if (component) \
	{ \
		component->getEventDispatcher().removeEventHandler(event_instance); \
	}

#define REMOVE_PLAYER_EVENT_HANDLER(component, event_name, event_instance) \
	if (component) \
	{ \
		component->getPlayer##event_name##Dispatcher().removeEventHandler(event_instance); \
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

void ComponentManager::AddEvents()
{
	// ADD_EVENT_HANDLER(actors, ActorEvents::Get());
	// ADD_PLAYER_EVENT_HANDLER(players, Spawn, PlayerEvents::Get());
	// ADD_PLAYER_EVENT_HANDLER(players, Connect, PlayerEvents::Get());
	// ADD_PLAYER_EVENT_HANDLER(players, Stream, PlayerEvents::Get());
	// ADD_PLAYER_EVENT_HANDLER(players, Text, PlayerEvents::Get());
	// ADD_PLAYER_EVENT_HANDLER(players, Shot, PlayerEvents::Get());
	// ADD_PLAYER_EVENT_HANDLER(players, Change, PlayerEvents::Get());
	// ADD_PLAYER_EVENT_HANDLER(players, Damage, PlayerEvents::Get());
	// ADD_PLAYER_EVENT_HANDLER(players, Click, PlayerEvents::Get());
	// ADD_PLAYER_EVENT_HANDLER(players, Check, PlayerEvents::Get());
}

void ComponentManager::RemoveEvents()
{
	// REMOVE_EVENT_HANDLER(actors, ActorEvents::Get());
	// REMOVE_PLAYER_EVENT_HANDLER(players, Spawn, PlayerEvents::Get());
	// REMOVE_PLAYER_EVENT_HANDLER(players, Connect, PlayerEvents::Get());
	// REMOVE_PLAYER_EVENT_HANDLER(players, Stream, PlayerEvents::Get());
	// REMOVE_PLAYER_EVENT_HANDLER(players, Text, PlayerEvents::Get());
	// REMOVE_PLAYER_EVENT_HANDLER(players, Shot, PlayerEvents::Get());
	// REMOVE_PLAYER_EVENT_HANDLER(players, Change, PlayerEvents::Get());
	// REMOVE_PLAYER_EVENT_HANDLER(players, Damage, PlayerEvents::Get());
	// REMOVE_PLAYER_EVENT_HANDLER(players, Click, PlayerEvents::Get());
	// REMOVE_PLAYER_EVENT_HANDLER(players, Check, PlayerEvents::Get());
}
