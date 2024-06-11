#include "../ComponentManager.hpp"

OMP_CAPI(CustomModel_AddCharModel, bool(int baseid, int newid, StringCharPtr dff, StringCharPtr textureLibrary))
{
	auto models = ComponentManager::Get()->models;
	if (!models)
	{
		return false;
	}

	bool ret = models->addCustomModel(ModelType::Skin, newid, baseid, dff, textureLibrary);
	return ret;
}

OMP_CAPI(CustomModel_AddSimpleModel, bool(int virtualWorld, int baseid, int newid, StringCharPtr dff, StringCharPtr textureLibrary))
{
	auto models = ComponentManager::Get()->models;
	if (!models)
	{
		return false;
	}

	bool ret = models->addCustomModel(ModelType::Object, newid, baseid, dff, textureLibrary, virtualWorld);
	return ret;
}

OMP_CAPI(CustomModel_AddSimpleModelTimed, bool(int virtualWorld, int baseid, int newid, StringCharPtr dff, StringCharPtr textureLibrary, int timeOn, int timeOff))
{
	auto models = ComponentManager::Get()->models;
	if (!models)
	{
		return false;
	}

	bool ret = models->addCustomModel(ModelType::Object, newid, baseid, dff, textureLibrary, virtualWorld, timeOn, timeOff);
	return ret;
}

OMP_CAPI(Player_GetCustomSkin, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	IPlayerCustomModelsData* data = queryExtension<IPlayerCustomModelsData>(player_);
	if (!data)
	{
		return 0;
	}
	auto skin = data->getCustomSkin();
	return skin;
}

OMP_CAPI(CustomModel_RedirectDownload, bool(objectPtr player, StringCharPtr url))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	IPlayerCustomModelsData* data = queryExtension<IPlayerCustomModelsData>(player_);
	if (!data)
	{
		return false;
	}
	if (!data->sendDownloadUrl(url))
	{
		ComponentManager::Get()->core->logLn(LogLevel::Warning, "This native can be used only within OnPlayerRequestDownload callback.");
		return false;
	}
	return true;
}

OMP_CAPI(CustomModel_FindModelFileNameFromCRC, int(int crc, ModifyableStringCharPtr output))
{
	auto models = ComponentManager::Get()->models;
	if (!models)
	{
		return false;
	}

	auto result = models->getModelNameFromChecksum(crc);
	auto len = result.length();
	COPY_STRING_TO_CAPI_STRING_VIEW(output, result.data(), len);
	return true;
}

OMP_CAPI(CustomModel_IsValid, bool(int modelId))
{
	auto models = ComponentManager::Get()->models;
	if (!models)
	{
		return false;
	}

	auto valid = models->isValidCustomModel(modelId);
	return valid;
}

OMP_CAPI(CustomModel_GetPath, bool(int modelId, ModifyableStringCharPtr dffPath, ModifyableStringCharPtr txdPath))
{
	auto models = ComponentManager::Get()->models;
	if (!models)
	{
		return false;
	}

	StringView dffPathSV {};
	StringView txdPathSV {};

	auto status = models->getCustomModelPath(modelId, dffPathSV, txdPathSV);

	COPY_STRING_TO_CAPI_STRING_VIEW(dffPath, dffPathSV.data(), dffPathSV.length());
	COPY_STRING_TO_CAPI_STRING_VIEW(txdPath, txdPathSV.data(), txdPathSV.length());

	return status;
}
