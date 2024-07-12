/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2024, open.mp team and contributors.
 */

#include "../ComponentManager.hpp"

OMP_CAPI(Checkpoint_SetPosition, void(objectPtr checkpoint, float x, float y, float z))
{
	ENTITY_CAST(ICheckpointData, checkpoint, checkpoint_);
	checkpoint_->setPosition({ x, y, z });
}

OMP_CAPI(Checkpoint_SetRadius, void(objectPtr checkpoint, float radius))
{
	ENTITY_CAST(ICheckpointData, checkpoint, checkpoint_);
	checkpoint_->setRadius(radius);
}

OMP_CAPI(Checkpoint_Enable, void(objectPtr checkpoint))
{
	ENTITY_CAST(ICheckpointData, checkpoint, checkpoint_);
	checkpoint_->enable();
}

OMP_CAPI(Checkpoint_Disable, void(objectPtr checkpoint))
{
	ENTITY_CAST(ICheckpointData, checkpoint, checkpoint_);
	checkpoint_->disable();
}

OMP_CAPI(Checkpoint_IsEnabled, bool(objectPtr checkpoint))
{
	ENTITY_CAST_RET(ICheckpointData, checkpoint, checkpoint_, false);
	return checkpoint_->isEnabled();
}

OMP_CAPI(Checkpoint_IsPlayerInside, bool(objectPtr checkpoint))
{
	ENTITY_CAST_RET(ICheckpointData, checkpoint, checkpoint_, false);
	return checkpoint_->isPlayerInside();
}


OMP_CAPI(RaceCheckpoint_SetType, void(objectPtr cp, int type))
{
	ENTITY_CAST(IRaceCheckpointData, cp, cp_);
	cp_->setType(RaceCheckpointType(type));
}

OMP_CAPI(RaceCheckpoint_SetPosition, void(objectPtr cp, float x, float y, float z))
{
	ENTITY_CAST(IRaceCheckpointData, cp, cp_);
	cp_->setPosition({ x, y, z });
}

OMP_CAPI(RaceCheckpoint_SetNextPosition, void(objectPtr cp, float x, float y, float z))
{
	ENTITY_CAST(IRaceCheckpointData, cp, cp_);
	cp_->setNextPosition({ x, y, z });
}

OMP_CAPI(RaceCheckpoint_SetRadius, void(objectPtr cp, float radius))
{
	ENTITY_CAST(IRaceCheckpointData, cp, cp_);
	cp_->setRadius(radius);
}

OMP_CAPI(RaceCheckpoint_Enable, void(objectPtr cp))
{
	ENTITY_CAST(IRaceCheckpointData, cp, cp_);
	cp_->enable();
}

OMP_CAPI(RaceCheckpoint_Disable, void(objectPtr cp))
{
	ENTITY_CAST(IRaceCheckpointData, cp, cp_);
	cp_->disable();
}

OMP_CAPI(RaceCheckpoint_IsEnabled, bool(objectPtr cp))
{
	ENTITY_CAST_RET(IRaceCheckpointData, cp, cp_, false);
	return cp_->isEnabled();
}

OMP_CAPI(RaceCheckpoint_IsPlayerInside, bool(objectPtr cp))
{
	ENTITY_CAST_RET(IRaceCheckpointData, cp, cp_, false);
	return cp_->isPlayerInside();
}
