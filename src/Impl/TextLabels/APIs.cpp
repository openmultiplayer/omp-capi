#include "../ComponentManager.hpp"

OMP_CAPI(TextLabel3D_Create, bool(StringCharPtr text, uint32_t color, float x, float y, float z, float drawDistance, int virtualWorld, bool los))
{
	ITextLabelsComponent* component = ComponentManager::Get()->textlabels;
	if (component)
	{
		ITextLabel* textlabel = component->create(text, Colour::FromRGBA(color), { x, y, z }, drawDistance, virtualWorld, los);
		if (textlabel)
		{
			return textlabel;
		}
	}
	return nullptr;
}

OMP_CAPI(TextLabel3D_Delete, bool(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	ComponentManager::Get()->textlabels->release(textlabel_->getID());
	return true;
}

OMP_CAPI(TextLabel3D_AttachToPlayer, bool(objectPtr textlabel, objectPtr player, float offsetX, float offsetY, float offsetZ))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	textlabel_->attachToPlayer(*player_, { offsetX, offsetY, offsetZ });
	return true;
}

OMP_CAPI(TextLabel3D_AttachToVehicle, bool(objectPtr textlabel, objectPtr vehicle, float offsetX, float offsetY, float offsetZ))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	POOL_ENTITY_RET(vehicles, IVehicle, vehicle, vehicle_, false);
	textlabel_->attachToVehicle(*vehicle_, { offsetX, offsetY, offsetZ });
	return true;
}

OMP_CAPI(TextLabel3D_UpdateText, bool(objectPtr textlabel, uint32_t color, StringCharPtr text))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	textlabel_->setColourAndText(Colour::FromRGBA(color), text);
	return true;
}

OMP_CAPI(TextLabel3D_IsValid, bool(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	if(!textlabels->get(textlabel_->getID())) return false;
	return true;
}

OMP_CAPI(TextLabel3D_IsStreamedIn, bool(objectPtr player, objectPtr textlabel))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	auto streamed = textlabel_->isStreamedInForPlayer(*player_);
	return streamed;
}

OMP_CAPI(TextLabel3D_GetText, bool(objectPtr textlabel, ModifyableStringCharPtr output))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	auto result = textlabel_->getText();
	auto len = result.length();
	output = UNCONST_STRING(result.data());
	return len;
}

OMP_CAPI(TextLabel3D_GetColor, uint32_t(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, 0);
	return textlabel_->getColour().RGBA();
}

OMP_CAPI(TextLabel3D_GetPos, bool(objectPtr textlabel, float* x, float* y, float* z))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	const Vector3& pos = textlabel_->getPosition();

	*x = pos.x;
	*y = pos.y;
	*z = pos.z;
	return true;
}

OMP_CAPI(TextLabel3D_SetDrawDistance, bool(objectPtr textlabel, float distance))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	textlabel_->setDrawDistance(distance);
	return true;
}

OMP_CAPI(TextLabel3D_GetDrawDistance, float(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, 0.0f);
	auto distance = textlabel_->getDrawDistance();
	return distance;
}

OMP_CAPI(TextLabel3D_GetLOS, bool(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	auto los = textlabel_->getTestLOS();
	return los;
}

OMP_CAPI(TextLabel3D_SetLOS, bool(objectPtr textlabel, bool status))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	textlabel_->setTestLOS(status);
	return true;
}

OMP_CAPI(TextLabel3D_GetVirtualWorld, int(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, 0);
	auto virtualWorld = textlabel_->getVirtualWorld();
	return virtualWorld;
}

OMP_CAPI(TextLabel3D_SetVirtualWorld, bool(objectPtr textlabel, int world))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	textlabel_->setVirtualWorld(world);
	return true;
}

OMP_CAPI(TextLabel3D_GetAttachedData, bool(objectPtr textlabel, int* attached_player, int* attached_vehicle))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	const TextLabelAttachmentData& data = textlabel_->getAttachmentData();

	*attached_player = data.playerID;
	*attached_vehicle = data.vehicleID;

	return true;
}

/*
	Per-Player TextLabel
*/

OMP_CAPI(PlayerTextLabel3D_Create, objectPtr(objectPtr player, StringCharPtr text, uint32_t color, float x, float y, float z, float drawDistance, objectPtr attachedPlayer, objectPtr attachedVehicle, bool los))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	IPlayerTextLabelData* labelData = queryExtension<IPlayerTextLabelData>(player_);
	if (labelData)
	{
		IPlayerTextLabel* textlabel = nullptr;

		if (attachedPlayer)
		{
			textlabel = labelData->create(text, Colour::FromRGBA(color), { x, y, z }, drawDistance, los, *(IPlayer*)attachedPlayer);
		}
		else if (attachedVehicle)
		{
			textlabel = labelData->create(text, Colour::FromRGBA(color), { x, y, z }, drawDistance, los, *(IVehicle*)attachedVehicle);
		}
		else
		{
			textlabel = labelData->create(text, Colour::FromRGBA(color), { x, y, z }, drawDistance, los);
		}

		if (textlabel)
		{
			return textlabel;
		}
	}
	return nullptr;
}

OMP_CAPI(PlayerTextLabel3D_Delete, bool(objectPtr player, objectPtr textlabel))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	auto data = queryExtension<IPlayerTextLabelData>(player_);
	if (!data)
	{
		return false;
	}
	data->release(textlabel_->getID());
	return true;
}

OMP_CAPI(PlayerTextLabel3D_UpdateText, bool(objectPtr player, objectPtr textlabel, uint32_t color, StringCharPtr text))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	textlabel_->setColourAndText(Colour::FromRGBA(color), text);
	return true;
}

OMP_CAPI(PlayerTextLabel3D_IsValid, bool(objectPtr player, objectPtr textlabel, bool* valid))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	if(!playerData->get(textlabel_->getID())) return false;
	return true;
}

OMP_CAPI(PlayerTextLabel3D_GetText, bool(objectPtr player, objectPtr textlabel, ModifyableStringCharPtr output))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	auto result = textlabel_->getText();
	int len = result.length();
	output = UNCONST_STRING(result.data());
	return len;
}

OMP_CAPI(PlayerTextLabel3D_GetColor, bool(objectPtr player, objectPtr textlabel, uint32_t* color))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	*color = textlabel_->getColour().RGBA();
	return true;
}

OMP_CAPI(PlayerTextLabel3D_GetPos, bool(objectPtr player, objectPtr textlabel, float* x, float* y, float* z))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	const Vector3& pos = textlabel_->getPosition();

	*x = pos.x;
	*y = pos.y;
	*z = pos.z;
	return true;
}

OMP_CAPI(PlayerTextLabel3D_SetDrawDistance, bool(objectPtr player, objectPtr textlabel, float distance))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	textlabel_->setDrawDistance(distance);
	return true;
}

OMP_CAPI(PlayerTextLabel3D_GetDrawDistance, float(objectPtr player, objectPtr textlabel))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0.0f);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, 0.0f);
	auto distance = textlabel_->getDrawDistance();
	return distance;
}

OMP_CAPI(PlayerTextLabel3D_GetLOS, bool(objectPtr player, objectPtr textlabel))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	auto los = textlabel_->getTestLOS();
	return los;
}

OMP_CAPI(PlayerTextLabel3D_SetLOS, bool(objectPtr player, objectPtr textlabel, bool status))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	textlabel_->setTestLOS(status);
	return true;
}

OMP_CAPI(PlayerTextLabel3D_GetVirtualWorld, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	return player_->getVirtualWorld();
}

OMP_CAPI(PlayerTextLabel3D_GetAttachedData, bool(objectPtr player, objectPtr textlabel, int* attached_player, int* attached_vehicle))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	const TextLabelAttachmentData& data = textlabel_->getAttachmentData();

	*attached_player = data.playerID;
	*attached_vehicle = data.vehicleID;

	return true;
}
