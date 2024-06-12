#include <stdint.h>

enum EventPriorityType
{
	EventPriorityType_Highest,
	EventPriorityType_FairlyHigh,
	EventPriorityType_Default,
	EventPriorityType_FairlyLow,
	EventPriorityType_Lowest,
};

struct EventArgs
{
	uint8_t size;
	void** data;
};

typedef bool (*EventCallback)(EventArgs args);
