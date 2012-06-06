#include "GameWorld.h"
#include "BoundingSphere.h"
#include "Bullet.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Constructor. Bullets live for 2s by default. */
Bullet::Bullet()
	:
	GameObject("Bullet"),
	mTimeToLive(5000),
	mDamage(10)
{
	mBoundingShape = new BoundingSphere(this, 2);
}

/** Construct a new bullet with given position, velocity, acceleration, angle, rotation and lifespan. */
Bullet::Bullet(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl)
	:
	GameObject("Bullet", p, v, a, h, r),
	mTimeToLive(ttl),
	mDamage(10)
{
	mBoundingShape = new BoundingSphere(this, 2);
}

/** Copy constructor. */
Bullet::Bullet(const Bullet& b)
	:
	GameObject(b),
    mTimeToLive(b.mTimeToLive),
    mDamage(b.mDamage)
{
	mBoundingShape = new BoundingSphere(this, 2);
}

/** Destructor. */
Bullet::~Bullet(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update bullet, removing it from game world if necessary. */
void Bullet::Update(int t)
{
	// Update position/velocity
	GameObject::Update(t);
	// Reduce time to live
	mTimeToLive = mTimeToLive - t;
	// Ensure time to live isn't negative
	if (mTimeToLive < 0) { mTimeToLive = 0; }
	// If time to live is zero then remove bullet from world
	if (mTimeToLive == 0) {
		if (mWorld) mWorld->RemoveObject(this);
	}
}

void Bullet::Render()
{
    GameObject::Render();
    if(mShape.GetPtr() == NULL)
    {
        glBegin(GL_LINE_STRIP);
            glColor4f(0.8, 0.2, 0.6, 1.0);
            glVertex3f(2.0, 0.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
        glEnd();
    }
}

bool Bullet::CollisionTest(SmartPtr<GameObject> o)
{
//	if (o->GetType() != GameObjectType("Asteroid")) return false;
//	if (o->GetType() != GameObjectType("Drone")) return false;
	if (mBoundingShape.GetPtr() == NULL) return false;
	if (o->GetBoundingShape().GetPtr() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Bullet::OnCollision(const GameObjectList &objects)
{
    for (GameObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
    {
        const GameObject& object = (*(*it));
        const GameObjectType& type = object.GetType();

        // Compare Object type
        if(type == GameObjectType("Drone"))
        {
            mWorld->RemoveObject(this);
        }
        if(type == GameObjectType("Asteroid"))
        {
            mWorld->RemoveObject(this);
        }
    }
}
