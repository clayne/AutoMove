#include "Extended\FastTravelConfirmCallback.h"


class FastTravelHook : public FastTravelConfirmCallback
{
public:
	static void Install();

private:
	static void Run(FastTravelConfirmCallback* a_this, Message a_msg);
	static inline REL::Relocation<decltype(Run)> _Run;
};
