#ifndef __TIMESYSTEM_H__
#define __TIMESYSTEM_H__

#include <list>
#include <queue>
#include <memory>
using namespace std::tr1;

#include "TimeController.h"
#include "TimeEvent.h"
#include "GlobalFunction.h"

class TimeController;

class TimeSystem;
typedef shared_ptr<TimeSystem> TimeSystemPtr;

class TimeSystem
{
public:
	TimeSystem()
	{
		startTime_ = GetTickClock();
	}

	~TimeSystem()
	{
		Shutdown();
	}

	void RegisterDelayTimeEvent( long delayTime, TimeEvent::TimeEventProc proc );

	void RegisterTimeController( TimeControllerPtr timeController )
	{
		timeControllerSet_.push_back( timeController );
	}

	bool Init()
	{
		startTime_ = GetTickClock();
		return true;
	}

	void Run()
	{
		UpdateTimeController();
		UpdateTimeEvent();
	}

	//更新时间控制器
	void UpdateTimeController();

	//更新时间事件
	void UpdateTimeEvent();

	// 去的当前时间
	long GetCurTime() { return GetTickCount() - startTime_; }

	void Shutdown();

	static TimeSystemPtr GetTimeSystem();

private:
	// 时间控制器列表
	list< TimeControllerPtr > timeControllerSet_;
	
	typedef priority_queue< TimeEventPtr, vector< TimeEventPtr >,
		TimeEventPtrCmp > TimeEventSet;

	// 时间触发事件列表
	TimeEventSet timeEventSet_; 	

	// 开始运行时间
	long startTime_;
};


#endif	// end of TimeSystem.h