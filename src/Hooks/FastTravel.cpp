#include "Hooks/FastTravel.h"
#include "Offsets.h"
#include "Events.h"


// 0 unk, 1 yes, 2 no, 3 marker
void FastTravelHook::Run(FastTravelConfirmCallback* a_this, Message a_msg)
{
	logger::trace("FastTravelHook: {}", a_msg);

	EventRegsHolder* events = EventRegsHolder::GetSingleton();
	events->fastTravel.QueueEvent(
		static_cast<std::underlying_type_t<Message>>(a_msg));

	_Run(a_this, a_msg);
}

void FastTravelHook::Install()
{
	Relocation<std::uintptr_t> vtbl{ RE::Offset::FastTravelConfirmCallback::Vtbl };
	_Run = vtbl.write_vfunc(0x1, Run);
};
