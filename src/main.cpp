/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, Amyr (iAmir) Ahmady
 */

#include <sdk.hpp>
#include "Impl/ComponentManager.hpp"

class CAPIComponent final : public IComponent
{
private:
	ICore* core_ = nullptr;

public:
	PROVIDE_UID(0x10467DD8D4C56FC6);

	~CAPIComponent()
	{
		
	}

	StringView componentName() const override
	{
		return "open.mp CAPI";
	}

	SemanticVersion componentVersion() const override
	{
		return SemanticVersion(0, 1, 0, 0);
	}

	void onLoad(ICore* c) override
	{
		core_ = c;
		core_->printLn("open.mp CAPI component loaded");
	}

	void onInit(IComponentList* components) override
	{
		ComponentManager::Get()->Init(core_, components);
	}

	void onReady() override
	{

	}

	void onFree(IComponent* component) override
	{

	}

	void free() override
	{
		delete this;
	}

	void reset() override
	{
	}
};

COMPONENT_ENTRY_POINT()
{
	return new CAPIComponent();
}
