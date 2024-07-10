/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, open.mp team and contributors.
 */

#include "../ComponentManager.hpp"

OMP_CAPI(TextLabel_Create, objectPtr(StringCharPtr text, uint32_t color, float x, float y, float z, float drawDistance, int virtualWorld, bool los, int* id))
{
	ITextLabelsComponent* component = ComponentManager::Get()->textlabels;
	if (component)
	{
		ITextLabel* textlabel = component->create(text, Colour::FromRGBA(color), { x, y, z }, drawDistance, virtualWorld, los);
		if (textlabel)
		{
			*id = textlabel->getID();
			return textlabel;
		}
	}
	return nullptr;
}

OMP_CAPI(TextLabel_Destroy, void(objectPtr textlabel))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	ComponentManager::Get()->textlabels->release(textlabel_->getID());
}

OMP_CAPI(TextLabel_FromID, objectPtr(int textlabelid))
{
	ITextLabelsComponent* component = ComponentManager::Get()->textlabels;
	if (component)
	{
		return component->get(textlabelid);
	}
	return nullptr;
}

OMP_CAPI(TextLabel_GetID, int(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	return textlabel_->getID();
}

OMP_CAPI(TextLabel_AttachToPlayer, void(objectPtr textlabel, objectPtr player, float offsetX, float offsetY, float offsetZ))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	POOL_ENTITY(players, IPlayer, player, player_);
	textlabel_->attachToPlayer(*player_, { offsetX, offsetY, offsetZ });
}

OMP_CAPI(TextLabel_DetachFromPlayer, void(objectPtr textlabel, float offsetX, float offsetY, float offsetZ))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->detachFromPlayer({ offsetX, offsetY, offsetZ });
}

OMP_CAPI(TextLabel_AttachToVehicle, void(objectPtr textlabel, objectPtr vehicle, float offsetX, float offsetY, float offsetZ))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	POOL_ENTITY(vehicles, IVehicle, vehicle, vehicle_);
	textlabel_->attachToVehicle(*vehicle_, { offsetX, offsetY, offsetZ });
}

OMP_CAPI(TextLabel_DetachFromVehicle, void(objectPtr textlabel, float offsetX, float offsetY, float offsetZ))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->detachFromVehicle({ offsetX, offsetY, offsetZ });
}

OMP_CAPI(TextLabel_UpdateText, void(objectPtr textlabel, uint32_t color, StringCharPtr text))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setColourAndText(Colour::FromRGBA(color), text);
}

OMP_CAPI(TextLabel_IsValid, bool(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	if (!textlabels->get(textlabel_->getID()))
		return false;
	return true;
}

OMP_CAPI(TextLabel_IsStreamedInForPlayer, bool(objectPtr textlabel, objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	auto streamed = textlabel_->isStreamedInForPlayer(*player_);
	return streamed;
}

OMP_CAPI(TextLabel_SetText, void(objectPtr textlabel, StringCharPtr text))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setText(text);
}

OMP_CAPI(TextLabel_GetText, void(objectPtr textlabel, OutputStringViewPtr output))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	auto result = textlabel_->getText();
	SET_CAPI_STRING_VIEW(output, result);
}

OMP_CAPI(TextLabel_SetColor, void(objectPtr textlabel, uint32_t color))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setColour(Colour::FromRGBA(color));
}

OMP_CAPI(TextLabel_GetColor, uint32_t(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, 0);
	return textlabel_->getColour().RGBA();
}

OMP_CAPI(TextLabel_SetPosition, void(objectPtr textlabel, float x, float y, float z))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setPosition({ x, y, z });
}

OMP_CAPI(TextLabel_GetPosition, void(objectPtr textlabel, float* x, float* y, float* z))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	const Vector3& pos = textlabel_->getPosition();

	*x = pos.x;
	*y = pos.y;
	*z = pos.z;
}

OMP_CAPI(TextLabel_SetDrawDistance, void(objectPtr textlabel, float distance))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setDrawDistance(distance);
}

OMP_CAPI(TextLabel_GetDrawDistance, float(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, 0.0f);
	auto distance = textlabel_->getDrawDistance();
	return distance;
}

OMP_CAPI(TextLabel_GetLOS, bool(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, false);
	auto los = textlabel_->getTestLOS();
	return los;
}

OMP_CAPI(TextLabel_SetLOS, void(objectPtr textlabel, bool status))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setTestLOS(status);
}

OMP_CAPI(TextLabel_GetVirtualWorld, int(objectPtr textlabel))
{
	POOL_ENTITY_RET(textlabels, ITextLabel, textlabel, textlabel_, 0);
	auto virtualWorld = textlabel_->getVirtualWorld();
	return virtualWorld;
}

OMP_CAPI(TextLabel_SetVirtualWorld, void(objectPtr textlabel, int world))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setVirtualWorld(world);
}

OMP_CAPI(TextLabel_GetAttachmentData, void(objectPtr textlabel, int* attached_player, int* attached_vehicle))
{
	POOL_ENTITY(textlabels, ITextLabel, textlabel, textlabel_);
	const TextLabelAttachmentData& data = textlabel_->getAttachmentData();

	*attached_player = data.playerID;
	*attached_vehicle = data.vehicleID;
}

/*
	Per-Player TextLabel
*/

OMP_CAPI(PlayerTextLabel_Create, objectPtr(objectPtr player, StringCharPtr text, uint32_t color, float x, float y, float z, float drawDistance, bool los, objectPtr attachedPlayer, objectPtr attachedVehicle))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	IPlayerTextLabelData* labelData = queryExtension<IPlayerTextLabelData>(player_);
	if (labelData)
	{
		IPlayerTextLabel* textlabel = nullptr;

		if (attachedPlayer)
		{
			textlabel = labelData->create(text, Colour::FromRGBA(color), { x, y, z }, drawDistance, los, *reinterpret_cast<IPlayer*>(attachedPlayer));
		}
		else if (attachedVehicle)
		{
			textlabel = labelData->create(text, Colour::FromRGBA(color), { x, y, z }, drawDistance, los, *reinterpret_cast<IVehicle*>(attachedVehicle));
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

OMP_CAPI(PlayerTextLabel_Destroy, void(objectPtr player, objectPtr textlabel))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_POOL_ENTITY(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	auto data = queryExtension<IPlayerTextLabelData>(player_);
	if (!data)
	{
		return;
	}
	data->release(textlabel_->getID());
	return;
}

OMP_CAPI(PlayerTextLabel_FromID, objectPtr(objectPtr player, int textlabelid))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, nullptr);
	IPlayerTextLabelData* labelData = queryExtension<IPlayerTextLabelData>(player_);
	if (labelData)
	{
		return labelData->get(textlabelid);
	}
	return nullptr;
}

OMP_CAPI(PlayerTextLabel_GetID, int(objectPtr player, objectPtr textlabel))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	return textlabel_->getID();
}

OMP_CAPI(PlayerTextLabel_UpdateText, void(objectPtr player, objectPtr textlabel, uint32_t color, StringCharPtr text))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_POOL_ENTITY(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	textlabel_->setColourAndText(Colour::FromRGBA(color), text);
}

OMP_CAPI(PlayerTextLabel_IsValid, bool(objectPtr player, objectPtr textlabel, bool* valid))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	if (!playerData->get(textlabel_->getID()))
		return false;
	return true;
}

OMP_CAPI(PlayerTextLabel_SetText, void(objectPtr player, objectPtr textlabel, StringCharPtr text))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_POOL_ENTITY(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	textlabel_->setText(text);
}

OMP_CAPI(PlayerTextLabel_GetText, void(objectPtr player, objectPtr textlabel, OutputStringViewPtr output))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_POOL_ENTITY(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	auto result = textlabel_->getText();
	SET_CAPI_STRING_VIEW(output, result);
}

OMP_CAPI(PlayerTextLabel_SetColor, void(objectPtr player, objectPtr textlabel, uint32_t color))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, 0);
	textlabel_->setColour(Colour::FromRGBA(color));
}

OMP_CAPI(PlayerTextLabel_GetColor, uint32_t(objectPtr player, objectPtr textlabel))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, 0);
	return textlabel_->getColour().RGBA();
}

OMP_CAPI(PlayerTextLabel_GetPos, void(objectPtr player, objectPtr textlabel, float* x, float* y, float* z))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_POOL_ENTITY(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	const Vector3& pos = textlabel_->getPosition();

	*x = pos.x;
	*y = pos.y;
	*z = pos.z;
}

OMP_CAPI(PlayerTextLabel_SetDrawDistance, void(objectPtr player, objectPtr textlabel, float distance))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_POOL_ENTITY(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	textlabel_->setDrawDistance(distance);
}

OMP_CAPI(PlayerTextLabel_GetDrawDistance, float(objectPtr player, objectPtr textlabel))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0.0f);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, 0.0f);
	auto distance = textlabel_->getDrawDistance();
	return distance;
}

OMP_CAPI(PlayerTextLabel_GetLOS, bool(objectPtr player, objectPtr textlabel))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	auto los = textlabel_->getTestLOS();
	return los;
}

OMP_CAPI(PlayerTextLabel_SetLOS, void(objectPtr player, objectPtr textlabel, bool status))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_POOL_ENTITY(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	textlabel_->setTestLOS(status);
}

OMP_CAPI(PlayerTextLabel_GetVirtualWorld, int(objectPtr player, objectPtr textlabel))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, 0);
	PLAYER_POOL_ENTITY_RET(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_, false);
	return textlabel_->getVirtualWorld();
}

OMP_CAPI(PlayerTextLabel_GetAttachedData, void(objectPtr player, objectPtr textlabel, int* attached_player, int* attached_vehicle))
{
	POOL_ENTITY(players, IPlayer, player, player_);
	PLAYER_POOL_ENTITY(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	const TextLabelAttachmentData& data = textlabel_->getAttachmentData();

	*attached_player = data.playerID;
	*attached_vehicle = data.vehicleID;
}
