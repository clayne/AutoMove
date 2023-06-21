#include "Events.h"
#include "Offsets.h"


void EventRegsHolder::Save(SKSE::SerializationInterface* a_intfc, std::uint32_t a_version)
{
	customMarker.Save(a_intfc, kCustomMarker, a_version);
	fastTravel.Save(a_intfc, kFastTravel, a_version);
	playerDialogue.Save(a_intfc, kPlayerDialogue, a_version);
}

void EventRegsHolder::Load(SKSE::SerializationInterface* a_intfc, std::uint32_t a_type)
{
	switch (a_type) {
	case kCustomMarker:
		customMarker.Load(a_intfc);
		break;
	case kFastTravel:
		fastTravel.Load(a_intfc);
		break;
	case kPlayerDialogue:
		playerDialogue.Load(a_intfc);
		break;
	default:
		logger::critical("Unrecognized record type"sv);
		break;
	}
}

void EventRegsHolder::Revert(SKSE::SerializationInterface*)
{
	customMarker.Clear();
	fastTravel.Clear();
	playerDialogue.Clear();
}
