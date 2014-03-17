#ifndef __DEFAULT_H__
#define __DEFAULT_H__

#define REGISTER_CONTROLLER( Name )		\
	friend class Name;

#define REGISTER_TARGET( classname ) \
	private: classname * target_;	\
	public: void SetTarget( void * target ) { target_ = (classname *)target; }	\
	public: void * GetTarget() { return target_; }

#define RegisterTimeControl( controller )	\
	TimeSystem::GetTimeSystem()->RegisterTimeController( controller );	\
	controller->SetTarget( this );

#define UnregisterTimeControl( controller )	\
	controller->QuitControl();				\
	controller = NULL;

#define RegisterInputControl( controller )	\
	InputSystem::GetInputSystem()->RegisterInputController( controller );	\
	controller->SetTarget( this );

#define UnregisterInputControl( controller )	\
	controller->QuitControl();					\
	controller = NULL;

#define RegisterBoundingControl( boundingObject, rect, isMovable )			\
	boundingObject->entity_ = IntersectionSystem::GetIntersectionSystem()->		\
		CreateBoundingRectangle( rect, isMovable );								\
	IntersectionSystem::GetIntersectionSystem()->AddBoundingObject(				\
		boundingObject, isMovable );											\
	boundingObject->SetTarget( this );

#define UnregisterBoundingControl( boundingObject )					\
	boundingObject->QuitControl();									\
	boundingObject = NULL;

//#define REGISTER_BOUNDINGSPHERE( boundingObject, rect, isMovable )				\
//	boundingObject->entity_ = IntersectionSystem::GetIntersectionSystem()->		\
//		CreateBoundingSPHERE( rect, isMovable );								\
//	IntersectionSystem::GetIntersectionSystem()->AddBoundingObject(				\
//		boundingObject, isMovable );											\
//	boundingObject->SetTarget( this );

#endif	// end of Default.h