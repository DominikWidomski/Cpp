#include <stdlib.h>

#include "GameUtil.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "Ore.h"

Ore::Ore() : GameObject("Ore")
{
	mAngle = rand() % 360;
	mRotation = rand() % 90;
	mPosition.x = rand()/4;
	mPosition.y = rand()/4;
	mPosition.z = 5.0;
//	mVelocity.x = 10.0 * cos(DEG2RAD*mAngle);
//	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
//	mVelocity.z = 0.0;
    mVelocity.x = 0.0;
    mVelocity.y = 0.0;
    mVelocity.z = 0.0;

    mValue = rand() % 20 + 40;

	mBoundingShape = new BoundingSphere(this, 2);
}

Ore::Ore(int x, int y) : GameObject("Ore")
{
    mAngle = rand() % 360;
	mRotation = rand() % 90;
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = 0.0;
    mVelocity.x = 0.0;
    mVelocity.y = 0.0;
    mVelocity.z = 0.0;

    mValue = rand() % 20 + 40;

	mBoundingShape = new BoundingSphere(this, 2);
}

Ore::~Ore(void)
{
}

void Ore::PreRender()
{
    GameObject::PreRender();

	// Rotate drawing around Z-axis to ship's angle
	glRotatef(mAngle,0.8,0.2,1);
}

bool Ore::CollisionTest(SmartPtr<GameObject> o)
{
    // Don't collide with objects of the same type
	if (GetType() == o->GetType()) return false;
	// If there's no bounding shape, don't do anything
	if (mBoundingShape.GetPtr() == NULL) return false;
	// If colliding object doesn't have a pointer to shape, don't do anything
	if (o->GetBoundingShape().GetPtr() == NULL) return false;
	// Otherwise, return the result of a collision test between bounding shapes
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Ore::OnCollision(const GameObjectList& objects)
{
    SmartPtr<GameObject> object;
    GameObjectType const* type = NULL;

    GameObjectList::const_iterator it = objects.begin();
    GameObjectList::const_iterator end = objects.end();

    for (; it != end; ++it)
    {
        object = *it;
        type = &(object->GetType());

        // Compare Object type
        if((*type) == GameObjectType("Spaceship"))
        {
            mWorld->RemoveObject(this);
            cout << "ORE COLIDES WITH SPACESHIP\n";
        }
    }
}
