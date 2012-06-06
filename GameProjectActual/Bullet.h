#ifndef __BULLET_H__
#define __BULLET_H__

#include "GameUtil.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl);
	Bullet(const Bullet& b);
	Bullet(const GameObject& go);
	virtual ~Bullet(void);

	virtual void Update(int t);
	void Render();

    void SetTimeToLive(int ttl) { mTimeToLive = ttl; }
	int GetTimeToLive(void) { return mTimeToLive; }

	void SetDamage(int d) { mDamage = d; }
    int GetDamage() { return mDamage; }

	bool CollisionTest(SmartPtr<GameObject> o);
	void OnCollision(const GameObjectList &objects);

protected:
	int mTimeToLive;
	int mDamage;
};

#endif
