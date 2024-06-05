#include "../ComponentManager.hpp"

OMP_CAPI(Menu_Create, bool(StringCharPtr title, uint32_t columns, float x, float y, float column1Width, float column2Width))
{
	IMenusComponent* component = ComponentManager::Get()->menus;
	if (component)
	{
		IMenu* menu = component->create(title, { x, y }, columns, column1Width, column2Width);
		if (menu)
		{
			return menu;
		}
	}
	return nullptr;
}

OMP_CAPI(Menu_Destroy, bool(objectPtr menu))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	ComponentManager::Get()->menus->release(menu_->getID());
	return true;
}

OMP_CAPI(Menu_AddItem, int(objectPtr menu, uint8_t column, StringCharPtr text))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, INVALID_MENU_ID);
	auto index = menu_->addCell(text, column);
	return index;
}

OMP_CAPI(Menu_SetColumnHeader, bool(objectPtr menu, uint8_t column, StringCharPtr headerTitle))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	menu_->setColumnHeader(headerTitle, column);
	return true;
}

OMP_CAPI(Menu_ShowForPlayer, bool(objectPtr menu, objectPtr player))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	menu_->showForPlayer(*player_);
	return true;
}

OMP_CAPI(Menu_HideForPlayer, bool(objectPtr menu, objectPtr player))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	menu_->hideForPlayer(*player_);
	return true;
}

OMP_CAPI(Menu_Disable, bool(objectPtr menu))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	menu_->disable();
	return true;
}

OMP_CAPI(Menu_DisableRow, bool(objectPtr menu, uint8_t row))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	menu_->disableRow(row);
	return true;
}

OMP_CAPI(Player_GetMenu, int(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, INVALID_MENU_ID);
	IPlayerMenuData* menuData = queryExtension<IPlayerMenuData>(player_);
	if (menuData)
	{
		auto id = menuData->getMenuID();
		return id;
	}
	return -1;
}

OMP_CAPI(Menu_IsValid, bool(objectPtr menu))
{
	if (ComponentManager::Get()->menus == nullptr)
	{
		return false;
	}

	IMenu* menu_ = reinterpret_cast<IMenu*>(menu);
	auto valid = menu_ != nullptr;
	return valid;
}

OMP_CAPI(Menu_IsDisabled, bool(objectPtr menu))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	auto disabled = !menu_->isEnabled();
	return disabled;
}

OMP_CAPI(Menu_IsRowDisabled, bool(objectPtr menu, int row))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	auto disabled = !menu_->isRowEnabled(row);
	return disabled;
}

OMP_CAPI(Menu_GetColumns, int(objectPtr menu))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, 0);
	auto columns = menu_->getColumnCount();
	return columns;
}

OMP_CAPI(Menu_GetItems, int(objectPtr menu, int column))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, 0);
	auto rows = menu_->getRowCount(column);
	return rows;
}

OMP_CAPI(Menu_GetPos, bool(objectPtr menu, float* x, float* y))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	auto pos = menu_->getPosition();
	*x = pos.x;
	*y = pos.y;
	return true;
}

OMP_CAPI(Menu_GetColumnWidth, bool(objectPtr menu, float* column1Width, float* column2Width))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	auto widths = menu_->getColumnWidths();
	*column1Width = widths.x;
	*column2Width = widths.y;
	return true;
}

OMP_CAPI(Menu_GetColumnHeader, int(objectPtr menu, int column, ModifyableStringCharPtr header))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	auto result = menu_->getColumnHeader(column);
	header = UNCONST_STRING(result.data());
	return result.length();
}

OMP_CAPI(Menu_GetItem, int(objectPtr menu, int column, int row, ModifyableStringCharPtr cell))
{
	POOL_ENTITY_RET(menus, IMenu, menu, menu_, false);
	auto result = menu_->getCell(column, row);
	cell = UNCONST_STRING(result.data());
	return result.length();
}
