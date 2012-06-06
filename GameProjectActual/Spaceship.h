#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

class Spaceship : public GameObject
{
public:
	Spaceship();
	Spaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	Spaceship(const Spaceship& s);
	virtual ~Spaceship(void);

	virtual void Update(int t);
	virtual void Render(void);

	virtual void Thrust(float t);
	virtual void Rotate(float r);
	virtual void Shoot(void);

	void SetSpaceshipShape(SmartPtr<Shape> spaceship_shape) { mSpaceshipShape = spaceship_shape; }
	void SetThrusterShape(SmartPtr<Shape> thruster_shape) { mThrusterShape = thruster_shape; }
	void SetBulletShape(SmartPtr<Shape> bullet_shape) { mBulletShape = bullet_shape; }

	bool CollisionTest(SmartPtr<GameObject> o);
	void OnCollision(const GameObjectList &objects);

private:
	float mThrust;

	int mFireTimer;
    int mFireReloadTime;
    int mHealth;

	SmartPtr<Shape> mSpaceshipShape;
	SmartPtr<Shape> mThrusterShape;
	SmartPtr<Shape> mBulletShape;
};

#endif
