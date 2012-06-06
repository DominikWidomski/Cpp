#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

class Asteroid : public GameObject
{
public:
	Asteroid();
	Asteroid(int x, int y);
	~Asteroid(void);

    bool SelectionTest(GLVector3f w);
	bool CollisionTest(SmartPtr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
};

#endif
