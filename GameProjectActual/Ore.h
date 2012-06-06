#ifndef __ORE_H__
#define __ORE_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

class Ore : public GameObject
{
public:
	Ore();
	Ore(int x, int y);
	~Ore(void);

	void PreRender();

	bool CollisionTest(SmartPtr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

	int GetValue() { return mValue; }

protected:
    int mValue;
};

#endif
