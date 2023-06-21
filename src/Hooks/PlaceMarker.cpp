#include "Hooks/PlaceMarker.h"
#include "Offsets.h"
#include "Events.h"


// 0 move, 1 leave, 2 remove
void PlaceMarkerHook::Run(PlacePlayerMarkerCallbackFunctor* a_this, Message a_msg)
{
	logger::trace("PlaceMarkerHook: {}", a_msg);

	EventRegsHolder* events = EventRegsHolder::GetSingleton();
	events->customMarker.QueueEvent(
		static_cast<std::underlying_type_t<Message>>(a_msg));

	_Run(a_this, a_msg);
}

void PlaceMarkerHook::Install()
{
	Relocation<std::uintptr_t> vtbl{ RE::Offset::PlacePlayerMarkerCallbackFunctor::Vtbl };
	_Run = vtbl.write_vfunc(0x1, Run);
};
