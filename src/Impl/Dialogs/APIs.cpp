#include "../ComponentManager.hpp"

OMP_CAPI(Dialog_Show, bool(objectPtr player, int dialog, int style, StringCharPtr title, StringCharPtr body, StringCharPtr button1, StringCharPtr button2))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	IPlayerDialogData* data = queryExtension<IPlayerDialogData>(player_);
	if (!data)
	{
		return false;
	}

	if (dialog == INVALID_DIALOG_ID)
	{
		static bool warned = false;
		if (!warned)
		{
			ComponentManager::Get()->core->logLn(LogLevel::Warning, "Invalid dialog ID %d used.  Use `Dialog_Hide()`.", dialog);
			warned = true;
		}

		data->hide(*player_);
		return true;
	}

	data->show(*player_, dialog & 0xFFFF, DialogStyle(style), title, body, button1, button2);
	return true;
}

OMP_CAPI(Player_GetDialog, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, INVALID_DIALOG_ID);
	IPlayerDialogData* data = queryExtension<IPlayerDialogData>(player_);
	auto dialog = data->getActiveID();
	return dialog;
}

OMP_CAPI(Player_GetDialogData, bool(objectPtr player, int* dialogid, int* style, ModifyableStringCharPtr title, ModifyableStringCharPtr body, ModifyableStringCharPtr button1, ModifyableStringCharPtr button2))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	IPlayerDialogData* data = queryExtension<IPlayerDialogData>(player_);
	DialogStyle styleVar {};
	StringView titleVar {};
	StringView bodyVar {};
	StringView button1Var {};
	StringView button2Var {};
	data->get(*dialogid, styleVar, titleVar, bodyVar, button1Var, button2Var);
	*style = int(styleVar);
	title = UNCONST_STRING(titleVar.data());
	body = UNCONST_STRING(bodyVar.data());
	button1 = UNCONST_STRING(button1Var.data());
	button2 = UNCONST_STRING(button2Var.data());
	return true;
}

OMP_CAPI(Dialog_Hide, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	IPlayerDialogData* dialog = queryExtension<IPlayerDialogData>(player_);
	if (dialog && dialog->getActiveID() != INVALID_DIALOG_ID)
	{
		dialog->hide(*player_);
		return true;
	}
	return true;
}
