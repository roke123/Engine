#include "TimeEvent.h"
#include "TimeSystem.h"

TimeEvent::TimeEvent( long delayTime, TimeEventProc proc )
	: proc_( proc )
{
	handleTime_ = delayTime + TimeSystem::GetTimeSystem()->GetCurTime();
}