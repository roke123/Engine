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

	//����ʱ�������
	void UpdateTimeController();

	//����ʱ���¼�
	void UpdateTimeEvent();

	// ȥ�ĵ�ǰʱ��
	long GetCurTime() { return GetTickCount() - startTime_; }

	void Shutdown();

	static TimeSystemPtr GetTimeSystem();

private:
	// ʱ��������б�
	list< TimeControllerPtr > timeControllerSet_;
	
	typedef priority_queue< TimeEventPtr, vector< TimeEventPtr >,
		TimeEventPtrCmp > TimeEventSet;

	// ʱ�䴥���¼��б�
	TimeEventSet timeEventSet_; 	

	// ��ʼ����ʱ��
	long startTime_;
};


#endif	// end of TimeSystem.h