#ifndef __MOVEMENTCONTROLLER_H__
#define __MOVEMENTCONTROLLER_H__

#include "SmartPtr.h"

using namespace idllib;

class GameObject;

class MovementController
{
public:
	MovementController( SmartPtr<GameObject> object );
	virtual ~MovementController(void);

	void Accelerate(float a);
	void Rotate(float r);

protected:
	SmartPtr<GameObject> mObject;
	float mAcceleration;
};

#endif