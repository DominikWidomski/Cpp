#ifndef __BOUNDINGSPHERE_H__
#define __BOUNDINGSPHERE_H__

#include "GameUtil.h"
#include "GameObjectType.h"
#include "BoundingShape.h"

class BoundingSphere : public BoundingShape
{
public:
	BoundingSphere() : BoundingShape("BoundingSphere"), mRadius(0) {}
	BoundingSphere(SmartPtr<GameObject> o, float r) : BoundingShape("BoundingSphere", o), mRadius(r) {}

	bool CollisionTest(SmartPtr<BoundingShape> bs) {
		if (GetType() == bs->GetType()) {
			BoundingSphere* bsphere = (BoundingSphere*) bs.GetPtr();
			GLVector3f pos1 = GetGameObject()->GetPosition();
			GLVector3f pos2 = bsphere->GetGameObject()->GetPosition();
			float distance = (pos2 - pos1).length();
			float collision_distance = GetRadius() + bsphere->GetRadius();
			return (distance <= collision_distance);
		}
		return false;
	}

	void SetRadius(float r) { mRadius = r; }
	float GetRadius() { return mRadius; }

protected:
	float mRadius;
};

#endif