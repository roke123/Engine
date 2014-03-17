#ifndef __TIMEEVENT_H__
#define __TIMEEVENT_H__

#include <memory>
using namespace std::tr1;

#include "GlobalFunction.h"

//前置声明
class TimeEventPtrCmp;
class TimeSystem;

class TimeEvent
{
	friend class TimeEventPtrCmp; 
	friend class TimeSystem;

	typedef void ( * TimeEventProc )();

	TimeEvent::TimeEvent( long delayTime, TimeEventProc proc );

	void Run()
	{
		proc_();
	}

	long GetHandleTime()
	{
		return handleTime_;
	}

private:
	//事件函数
	TimeEventProc proc_;

	//事件执行的时间
	long handleTime_;
};	// end of class TimeEvent

typedef shared_ptr<TimeEvent> TimeEventPtr;

//用于比较TimeEvent的handleTime的函数对象
class TimeEventPtrCmp
{
public:
	bool operator () ( const TimeEventPtr lh, const TimeEventPtr rh )
	{
		if( lh->handleTime_ < rh->handleTime_ )
			return true;

		return false;
	}
};

#endif	// end of TimeEvent.h