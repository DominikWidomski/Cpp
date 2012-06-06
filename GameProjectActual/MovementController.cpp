#include "GLVector.h"
#include "GameObject.h"
#include "MovementController.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

MovementController::MovementController(SmartPtr<GameObject> object)
	: mObject(object),
	  mAcceleration(0)
{
}

MovementController::~MovementController()
{
}

// PROTECTED INSTANCE METHODS /////////////////////////////////////////////////

void MovementController::Accelerate(GLfloat a)
{
	float angle = mObject->GetAngle();
	GLVector3f heading(cos(DEG2RAD*angle), sin(DEG2RAD*angle), 0);
	mObject->SetAcceleration(heading * a);
	mAcceleration = a;
}

void MovementController::Rotate(GLfloat r)
{
	mObject->SetRotation(r);
	Accelerate(mAcceleration);
}