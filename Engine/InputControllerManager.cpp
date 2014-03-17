#include "InputSystem.h"
#include "InputControllerManager.h"


InputControllerManager::InputControllerManager( InputSystem * inputSystem )
{
	inputSystem_ = inputSystem;
}

void InputControllerManager::RegisterController( InputControllerPtr controller )
{
	controllerSet_.push_back( controller );
}

void InputControllerManager::Update()
{
	list< InputControllerPtr >::iterator ite;
	ite = controllerSet_.begin();

	for( ; ite != controllerSet_.end(); )
	{
		InputControllerPtr temp = *ite;

		if( temp->IsAvailable() )
			temp->InputHandler( inputSystem_ );
		else
		{
			controllerSet_.erase( ite ++ );
			continue;
		}

		++ ite;
	}
}

void InputControllerManager::ClearManager()
{
	controllerSet_.clear();
}