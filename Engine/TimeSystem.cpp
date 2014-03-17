#include "TimeSystem.h"

void TimeSystem::UpdateTimeController()
{
	list< TimeControllerPtr >::iterator ite;

	ite = timeControllerSet_.begin();
	while( ite != timeControllerSet_.end() )
	{
		TimeControllerPtr temp = *ite;
		if( temp->IsAvailable() )
		{
			long delte = GetTickCount() - temp->lastTime_;
			temp->lastTime_ = GetTickClock();
			temp->TimeHandler( delte );
		}
		else
		{
			timeControllerSet_.erase( ite ++ );
			continue;
		}

		++ ite;
	}
}

void TimeSystem::RegisterDelayTimeEvent( long delayTime, TimeEvent::TimeEventProc proc )
{
	timeEventSet_.push( TimeEventPtr( new TimeEvent( delayTime, proc ) ) );
}

void TimeSystem::UpdateTimeEvent()
{
	long now = GetCurTime();

	if( !timeEventSet_.empty() )
	{
		TimeEventPtr temp = timeEventSet_.top();
		while( temp->handleTime_ < now )
		{
			timeEventSet_.pop();
			temp->Run();
		}
	}
}

void TimeSystem::Shutdown()
{
	timeControllerSet_.clear();

	while( !timeEventSet_.empty() )
		timeEventSet_.pop();
}

TimeSystemPtr TimeSystem::GetTimeSystem()
{
	static TimeSystemPtr timeSystem = NULL;

	if( timeSystem == NULL )
		timeSystem.reset( new TimeSystem );

	return timeSystem;
}