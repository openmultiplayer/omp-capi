#include "../ComponentManager.hpp"

OMP_CAPI(TextDraw_Create, objectPtr(float x, float y, StringCharPtr text))
{
	ITextDrawsComponent* component = ComponentManager::Get()->textdraws;
	if (component)
	{
		ITextDraw* textdraw = component->create({ x, y }, text);
		if (textdraw)
		{
			return textdraw;
		}
	}
	return nullptr;
}

OMP_CAPI(TextDraw_Destroy, bool(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	ComponentManager::Get()->textdraws->release(textdraw_->getID());
	return true;
}

OMP_CAPI(TextDraw_IsValid, bool(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	return true;
}

OMP_CAPI(TextDraw_IsVisibleForPlayer, bool(objectPtr player, objectPtr textdraw))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	return textdraw_->isShownForPlayer(*player_);
}

OMP_CAPI(TextDraw_SetLetterSize, bool(objectPtr textdraw, float sizeX, float sizeY))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setLetterSize({ sizeX, sizeY });
	return true;
}

OMP_CAPI(TextDraw_SetTextSize, bool(objectPtr textdraw, float sizeX, float sizeY))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setTextSize({ sizeX, sizeY });
	return true;
}

OMP_CAPI(TextDraw_SetAlignment, bool(objectPtr textdraw, int alignment))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setAlignment(TextDrawAlignmentTypes(alignment));
	return true;
}

OMP_CAPI(TextDraw_SetColor, bool(objectPtr textdraw, uint32_t color))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setColour(Colour::FromRGBA(color));
	return true;
}

OMP_CAPI(TextDraw_SetUseBox, bool(objectPtr textdraw, bool use))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->useBox(use);
	return true;
}

OMP_CAPI(TextDraw_SetBoxColor, bool(objectPtr textdraw, uint32_t color))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setBoxColour(Colour::FromRGBA(color));
	return true;
}

OMP_CAPI(TextDraw_SetShadow, bool(objectPtr textdraw, int size))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setShadow(size);
	return true;
}

OMP_CAPI(TextDraw_SetOutline, bool(objectPtr textdraw, int size))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setOutline(size);
	return true;
}

OMP_CAPI(TextDraw_SetBackgroundColor, bool(objectPtr textdraw, uint32_t color))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setBackgroundColour(Colour::FromRGBA(color));
	return true;
}

OMP_CAPI(TextDraw_SetFont, bool(objectPtr textdraw, int font))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setStyle(TextDrawStyle(font));
	return true;
}

OMP_CAPI(TextDraw_SetSetProportional, bool(objectPtr textdraw, bool set))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setProportional(set);
	return true;
}

OMP_CAPI(TextDraw_SetSelectable, bool(objectPtr textdraw, bool set))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setSelectable(set);
	return true;
}

OMP_CAPI(TextDraw_ShowForPlayer, bool(objectPtr player, objectPtr textdraw))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->showForPlayer(*player_);
	return true;
}

OMP_CAPI(TextDraw_HideForPlayer, bool(objectPtr player, objectPtr textdraw))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->hideForPlayer(*player_);
	return true;
}

OMP_CAPI(TextDraw_ShowForAll, bool(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	IPlayerPool* pool = ComponentManager::Get()->players;
	for (IPlayer* player : pool->entries())
	{
		textdraw_->showForPlayer(*player);
	}
	return true;
}

OMP_CAPI(TextDraw_HideForAll, bool(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	IPlayerPool* pool = ComponentManager::Get()->players;
	for (IPlayer* player : pool->entries())
	{
		textdraw_->hideForPlayer(*player);
	}
	return true;
}

OMP_CAPI(TextDraw_SetString, bool(objectPtr textdraw, StringCharPtr text))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setText(text);
	return true;
}

OMP_CAPI(TextDraw_SetPreviewModel, bool(objectPtr textdraw, int model))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setPreviewModel(model);
	return true;
}

OMP_CAPI(TextDraw_SetPreviewRot, bool(objectPtr textdraw, float rotationX, float rotationY, float rotationZ, float zoom))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setPreviewRotation({ rotationX, rotationY, rotationZ });
	textdraw_->setPreviewZoom(zoom);
	return true;
}

OMP_CAPI(TextDraw_SetPreviewVehCol, bool(objectPtr textdraw, int color1, int color2))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setPreviewVehicleColour(color1, color2);
	return true;
}

OMP_CAPI(TextDraw_SetPos, bool(objectPtr textdraw, float x, float y))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	textdraw_->setPosition({ x, y });
	return true;
}

OMP_CAPI(TextDraw_GetString, int(objectPtr textdraw, ModifyableStringCharPtr text))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, 0);
	auto textStr = textdraw_->getText();
	int len = textStr.length();
	text = UNCONST_STRING(textStr.data());
	return len;
}

OMP_CAPI(TextDraw_GetLetterSize, bool(objectPtr textdraw, float* sizeX, float* sizeY))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	const Vector2& size = textdraw_->getLetterSize();
	*sizeX = size.x;
	*sizeY = size.y;
	return true;
}

OMP_CAPI(TextDraw_GetTextSize, bool(objectPtr textdraw, float* sizeX, float* sizeY))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	const Vector2& size = textdraw_->getTextSize();
	*sizeX = size.x;
	*sizeY = size.y;
	return true;
}

OMP_CAPI(TextDraw_GetPos, bool(objectPtr textdraw, float* x, float* y))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	const Vector2& pos = textdraw_->getPosition();
	*x = pos.x;
	*y = pos.y;
	return true;
}

OMP_CAPI(TextDraw_GetColor, int(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	return textdraw_->getLetterColour().RGBA();
}

OMP_CAPI(TextDraw_GetBoxColor, int(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	return textdraw_->getBoxColour().RGBA();
}

OMP_CAPI(TextDraw_GetBackgroundColor, int(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	return textdraw_->getBackgroundColour().RGBA();
}

OMP_CAPI(TextDraw_GetShadow, int(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, 0);
	return textdraw_->getShadow();
}

OMP_CAPI(TextDraw_GetOutline, int(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, 0);
	return textdraw_->getOutline();
}

OMP_CAPI(TextDraw_GetFont, int(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	return static_cast<int>(textdraw_->getStyle());
}

OMP_CAPI(TextDraw_IsBox, bool(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	return textdraw_->hasBox();
}

OMP_CAPI(TextDraw_IsProportional, bool(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	return textdraw_->isProportional();
}

OMP_CAPI(TextDraw_IsSelectable, bool(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	return textdraw_->isSelectable();
}

OMP_CAPI(TextDraw_GetAlignment, int(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, 0);
	return static_cast<int>(textdraw_->getAlignment());
}

OMP_CAPI(TextDraw_GetPreviewModel, int(objectPtr textdraw))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, 0);
	return textdraw_->getPreviewModel();
}

OMP_CAPI(TextDraw_GetPreviewRot, bool(objectPtr textdraw, float* x, float* y, float* z, float* zoom))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	const Vector3& rotation = textdraw_->getPreviewRotation();
	*x = rotation.x;
	*y = rotation.y;
	*z = rotation.z;
	*zoom = textdraw_->getPreviewZoom();
	return true;
}

OMP_CAPI(TextDraw_GetPreviewVehColor, bool(objectPtr textdraw, int* color1, int* color2))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	Pair<int, int> colors = textdraw_->getPreviewVehicleColour();
	*color1 = colors.first;
	*color2 = colors.second;
	return true;
}

OMP_CAPI(TextDraw_SetStringForPlayer, bool(objectPtr textdraw, objectPtr player, StringCharPtr text))
{
	POOL_ENTITY_RET(textdraws, ITextDraw, textdraw, textdraw_, false);
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	textdraw_->setTextForPlayer(*player_, text);
	return true;
}

/*
	Per-Player GangZones
*/


