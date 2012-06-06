#ifndef __BOUNDINGSHAPE_H__
#define __BOUNDINGSHAPE_H__

#include "GameUtil.h"
#include "GameObjectType.h"
#include "GameObject.h"

class BoundingShape
{
public:
	BoundingShape(char const * const type_name) : mType(type_name) {}
	BoundingShape(char const * const type_name, SmartPtr<GameObject> o)
		: mType(type_name), mGameObject(o) {}

	virtual bool CollisionTest(SmartPtr<BoundingShape> bshape) { return false; }

	const GameObjectType& GetType() const { return mType; }

	virtual void SetGameObject(SmartPtr<GameObject> o) { mGameObject = o; }
	virtual SmartPtr<GameObject> GetGameObject() { return mGameObject; }

protected:
	GameObjectType mType;
	SmartPtr<GameObject> mGameObject;
};

#endif
