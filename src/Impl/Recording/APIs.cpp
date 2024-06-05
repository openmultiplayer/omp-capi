#include "../ComponentManager.hpp"

OMP_CAPI(Recording_Start, bool(objectPtr player, int type, StringCharPtr file))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	IPlayerRecordingData* recording = queryExtension<IPlayerRecordingData>(player_);
	if (recording)
	{
		recording->start(PlayerRecordingType(type), file);
		return true;
	}
	return false;
}

OMP_CAPI(Recording_Stop, bool(objectPtr player))
{
	POOL_ENTITY_RET(players, IPlayer, player, player_, false);
	IPlayerRecordingData* recording = queryExtension<IPlayerRecordingData>(player_);
	if (recording)
	{
		recording->stop();
		return true;
	}
	return false;
}
