#include "Papyrus.h"
#include "Events.h"

namespace Papyrus
{
	void ForceDestinationMarkerIntoAliasID(TESQuest* quest, std::uint32_t index)
	{
		PlayerCharacter* player = PlayerCharacter::GetSingleton();

		NiPointer<TESObjectREFR> marker;
		TESObjectREFR::LookupByHandle(player->unk924, marker);

		if (marker) {
			quest->ForceRefIntoAliasID(index, marker.get());
		}
	}

	Actor* GetCurrentMount(StaticFunctionTag*, Actor* actor)
	{
		ExtraInteraction* extra = static_cast<ExtraInteraction*>(actor->extraList.GetByType(ExtraDataType::kInteraction));
		if (extra) {
			NiPointer<Actor> mount = extra->interaction->actor.get();
			if (mount) {
				return mount.get();
			}
		}
		return nullptr;
	}

	bool IsCustomDestinationActive(StaticFunctionTag*)
	{
		PlayerCharacter* player = PlayerCharacter::GetSingleton();
		return player->unk924 ? true : false;
	}

	void RegisterForCustomMarkerChange(TESQuest* quest)
	{
		auto events = EventRegsHolder::GetSingleton();
		events->customMarker.Register(quest);
	}

	void UnregisterForCustomMarkerChange(TESQuest* quest)
	{
		auto events = EventRegsHolder::GetSingleton();
		events->customMarker.Unregister(quest);
	}

	void RegisterForPlayerDialogue(TESQuest* quest)
	{
		auto events = EventRegsHolder::GetSingleton();
		events->playerDialogue.Register(quest);
	}

	void UnregisterForPlayerDialogue(TESQuest* quest)
	{
		auto events = EventRegsHolder::GetSingleton();
		events->playerDialogue.Unregister(quest);
	}

	bool RegisterFuncs(BSScript::IVirtualMachine* a_vm)
	{
		a_vm->RegisterFunction("ForceDestinationMarkerIntoAliasID", "AutoMove", ForceDestinationMarkerIntoAliasID);
		a_vm->RegisterFunction("IsCustomDestinationActive", "AutoMove", IsCustomDestinationActive);
		a_vm->RegisterFunction("RegisterForCustomMarkerChange", "AutoMove", RegisterForCustomMarkerChange);
		a_vm->RegisterFunction("UnregisterForCustomMarkerChange", "AutoMove", UnregisterForCustomMarkerChange);
		a_vm->RegisterFunction("RegisterForPlayerDialogue", "AutoMove", RegisterForPlayerDialogue);
		a_vm->RegisterFunction("UnregisterForPlayerDialogue", "AutoMove", UnregisterForPlayerDialogue);
		a_vm->RegisterFunction("GetCurrentMount", "AutoMove", GetCurrentMount);		

		logger::info("Papyrus functions registered");

		return true;
	}
}
