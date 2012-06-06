#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "GameUtil.h"
#include "GameObject.h"

class Explosion : public GameObject
{
public:
	Explosion();
	Explosion(GLVector3f p, GLVector3f v, GLfloat h, GLfloat r);
	Explosion(const Explosion& e);
	virtual ~Explosion(void);

	virtual void Update(int t);
};

#endif
