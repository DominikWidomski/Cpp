#ifndef __ASTEROIDORE_H__
#define __ASTEROIDORE_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

class AsteroidOre : public GameObject
{
public:
	AsteroidOre();
	AsteroidOre(int x, int y);
	~AsteroidOre(void);

    bool SelectionTest(GLVector3f w);
	bool CollisionTest(SmartPtr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
};

#endif

