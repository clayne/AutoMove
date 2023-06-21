#include "Hooks/PlayerDialogue.h"
#include "Offsets.h"
#include "Events.h"


void PlayerDialogueHook::SetDialogueWithPlayer(Actor* a_this, bool a_flag, bool a_forceGreet, TESTopicInfo* a_topic)
{
	logger::trace("SetDialogueWithPlayer {} {}", a_flag, a_forceGreet);

	EventRegsHolder* events = EventRegsHolder::GetSingleton();
	events->playerDialogue.QueueEvent(a_this, a_flag);

	_SetDialogueWithPlayer(a_this, a_flag, a_forceGreet, a_topic);
}

void PlayerDialogueHook::Install()
{
	Relocation<std::uintptr_t> vtbl{ RE::Offset::Character::Vtbl };
	_SetDialogueWithPlayer = vtbl.write_vfunc(0x41, SetDialogueWithPlayer); // 65
};
