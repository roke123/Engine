#ifndef __INPUTCONTROLLERMANAGER_H__
#define __INPUTCONTROLLERMANAGER_H__

#include <list>
using namespace std;

#include "InputController.h"

class InputController;

class InputControllerManager
{
public:
	InputControllerManager( InputSystem * inputSystem );

	~InputControllerManager()
	{
		ClearManager();
	}

	void RegisterController( InputControllerPtr controller );

	void Update();

	void ClearManager();

private:
	list< InputControllerPtr > controllerSet_;

	InputSystem * inputSystem_;
};	// end of class InputControllerManager

#endif	// end of InputControllerManager.h