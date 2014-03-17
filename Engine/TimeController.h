#ifndef __TIMECONTROLLER_H__
#define __TIMECONTROLLER_H__

#include "GlobalFunction.h"
#include "Controller.h"
#include "TimeSystem.h"

#include <memory>
using namespace std::tr1;

class TimeController : public Controller
{
	friend class TimeSystem;
public:
	TimeController() : Controller()
	{
		lastTime_ = GetTickClock();
	}

	virtual ~TimeController() {};

	virtual void TimeHandler( long delta ) = 0;

private:
	long lastTime_;
};

typedef shared_ptr<TimeController> TimeControllerPtr;

#endif	// end of TimeController