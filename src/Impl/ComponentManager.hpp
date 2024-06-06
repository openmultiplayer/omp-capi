#pragma once
#include <variant>

#include "../Utils/Singleton.hpp"
#include "../Utils/MacroMagic.hpp"

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

#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

using OutputOnlyString = std::variant<bool, StringView, Impl::String>;

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

	/// Store open.mp components
	void Init(ICore* c, IComponentList* clist);

	// Add event handlers to components' event dispatchers
	void AddEvents();

	// Remove event handlers from components' event dispatchers
	void RemoveEvents();

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

private:
	IComponentList* componentList = nullptr;
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
	auto playerData = GetPlayerData<pool_type>(player);                                     \
	if (playerData == nullptr)                                                              \
		return failret;                                                                        \
	entity_type* entity_output = reinterpret_cast<entity_type*>(entity);                       \
	if (entity_output == nullptr)                                                              \
		return failret;

#define PLAYER_DATA_RET(player, entity_type, entity_output, failret) \
	auto entity_output = GetPlayerData<entity_type>(player);         \
	if (entity_output == nullptr)                                    \
	return failret

#define COPY_STRING(dest, src, len) \
	memcpy(dest, src, len);         \
	dest[len - 1] = '\0'

#define UNCONST_STRING(str) \
	const_cast<char*>(str)
