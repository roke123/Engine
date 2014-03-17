#ifndef __INPUTCONTROLLER_H__
#define __INPUTCONTROLLER_H__

class InputSystem;

#include <memory>
using namespace std::tr1;

#include "InputSystem.h"
#include "Controller.h"

class InputController : public Controller
{
public:
	//构造函数
	InputController() : Controller()
	{
		//留空
	}

	//虚析构函数
	virtual ~InputController(){}

	virtual void InputHandler( InputSystem * inputSystem ) = 0;
};	// end of InputController

typedef shared_ptr<InputController> InputControllerPtr;

#endif	// end of InputController