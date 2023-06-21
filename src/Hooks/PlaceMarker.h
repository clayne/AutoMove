#include "Extended\PlacePlayerMarkerCallbackFunctor.h"


class PlaceMarkerHook : public PlacePlayerMarkerCallbackFunctor
{
public:
	static void Install();
	
private:
	static void Run(PlacePlayerMarkerCallbackFunctor* a_this, Message a_msg);
	static inline REL::Relocation<decltype(Run)> _Run;
};
