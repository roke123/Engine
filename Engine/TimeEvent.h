#ifndef __TIMEEVENT_H__
#define __TIMEEVENT_H__

#include <memory>
using namespace std::tr1;

#include "GlobalFunction.h"

//ǰ������
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
	//�¼�����
	TimeEventProc proc_;

	//�¼�ִ�е�ʱ��
	long handleTime_;
};	// end of class TimeEvent

typedef shared_ptr<TimeEvent> TimeEventPtr;

//���ڱȽ�TimeEvent��handleTime�ĺ�������
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