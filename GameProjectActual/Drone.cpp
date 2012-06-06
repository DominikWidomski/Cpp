#include <stdlib.h>

#include "GameUtil.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "Drone.h"
#include "Bullet.h"
#include <cmath>

class GameObjectType;

Drone::Drone() : GameObject("Drone"), mSpeed(0.0), mMaxSpeed(5.0)
{
    mAngle = rand() % 360;
    mRotation = 0;
    mPosition.x = rand()/2;
    mPosition.y = rand()/2;
    mPosition.z = 0.0;
    mVelocity.x = mSpeed * cos(DEG2RAD*mAngle);
    mVelocity.y = mSpeed * sin(DEG2RAD*mAngle);
    mVelocity.z = 0.0;

    mFireTimer = 0;
    mFireReloadTime = 1000.0;
    mHealth = 100.0;

    mBoundingShape = new BoundingSphere(this,4);
}

Drone::Drone(int _x, int _y) : GameObject("Drone"), mSpeed(0.0), mMaxSpeed(5.0)
{
    mAngle = rand() % 360;
    mRotation = 0;
    mPosition.x = _x;
    mPosition.y = _y;
    mPosition.z = 0.0;
    mVelocity.x = mSpeed * cos(DEG2RAD*mAngle);
    mVelocity.y = mSpeed * sin(DEG2RAD*mAngle);
    mVelocity.z = 0.0;

    mFireTimer = 0;
    mFireReloadTime = 1000.0;
    mHealth = 100.0;

    mBoundingShape = new BoundingSphere(this,4);
}

Drone::~Drone(void)
{
}

// PUBLIC INSTANCE METHODS /////////////////////////////////////////

/** Update this spaceship. */
void Drone::Update(int t)
{
    // Calculate seconds since last update
	float dt = t / 1000.0f;

    if(mOrder.GetPtr() != NULL){
        //cout << "HAZ ORDER\n";
        mOrder->Update(t, (GameObject*)this);
    } else {
        //cout << "DOESN'T HAZ ORDER\n";
    }

    // Update Acceleration
    mAcceleration.x = mSpeed*cos(DEG2RAD*mAngle);
    mAcceleration.y = mSpeed*sin(DEG2RAD*mAngle);
    // Update Velocity
//	mVelocity.x += mAcceleration.x * dt;
//	mVelocity.y += mAcceleration.y * dt;
////    mVelocity.z += mAcceleration.z * dt;
    // Update Position
	mPosition.x += mAcceleration.x * dt;
	mPosition.y += mAcceleration.y * dt;
//    mPosition.z += mVelocity.z * dt;
    // Reset acceleration to 0
	mAcceleration = GLVector3f(0,0,0);

	// Update sprite if one exists
	if (mSprite.GetPtr() != NULL) mSprite->Update(t);
	// If in world, wrap position
	if (mWorld) { mWorld->WrapXY(mPosition.x, mPosition.y); }

    //mAngle += 50 * dt;
    mAngle = fmod(mAngle, 360);

    if(mFireTimer > 0) mFireTimer -= t;
}

void Drone::Render(void)
{
    GameObject::Render();

	// Rotate back to cancel the object rotation to draw the selection box
	glRotatef(-mAngle,0,0,1);

    if(mSelectedShape.GetPtr() != NULL && mSelected) mSelectedShape->Render();
}

void Drone::ShootAtTarget(SmartPtr<GameObject> t)
{
    if(mFireTimer > 0) return;

    // @todo whole firing here
    cout << "Firing\n";

    // Check the world exists
	if (!mWorld) return;
	// Construct a unit length vector in the direction the spaceship is headed
	GLVector3f drone_heading(cos(DEG2RAD*mAngle), sin(DEG2RAD*mAngle), 0);
	drone_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f bullet_position = mPosition + (drone_heading * 10);
	// Calculate how fast the bullet should travel
	float bullet_speed = 51 + mVelocity.dot(drone_heading);
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + drone_heading * bullet_speed;
	// Construct a new bullet
	SmartPtr<GameObject> bullet =
		new Bullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000);
	bullet->SetShape(mBulletShape);
	// Add the new bullet to the game world
	mWorld->AddObject(bullet);

    mFireTimer = mFireReloadTime;
}

bool Drone::SelectionTest(GLVector3f w)
{
    float distance = (mPosition - w).length();
    BoundingSphere* bSphere = (BoundingSphere*) mBoundingShape.GetPtr();
    return (distance <= bSphere->GetRadius());
}

bool Drone::CollisionTest(SmartPtr<GameObject> o)
{
//    if (o->GetType() != GameObjectType("Bullet")) return false;
    if (o->GetType() == GameObjectType("Drone")) return false;
	if (GetType() == o->GetType()) return false;
	if (mBoundingShape.GetPtr() == NULL) return false;
	if (o->GetBoundingShape().GetPtr() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Drone::OnCollision(const GameObjectList& objects)
{
    SmartPtr<GameObject> object;
    GameObjectType const* type = NULL;

    GameObjectList::const_iterator it = objects.begin();
    GameObjectList::const_iterator end = objects.end();

    for (; it != end; ++it)
    {
//        const GameObjectType * type = &((*it)->GetType() );

        object = *it;
        type = &(object->GetType());
//        const char * type_name = object->GetType().GetTypeName();
//        cout << type_name << ";" << endl;

        // Compare Object type
        if((*type) == GameObjectType("Bullet"))
        {
            // TODO add damage related stuff to GameObject which should allow you to bypass this whole awkward pointer stuff here...
            Bullet* b = (Bullet*) object.GetPtr();
//            cout << "colision with bullet" << endl;
//            Bullet* b = dynamic_cast<Bullet*>(object.GetPtr());

            int damage = b->GetDamage();
            int health = mHealth;
            int newHealth = mHealth - damage;

            DealDamage(b->GetDamage());
            //cout << "HEALTH " << mHealth << endl;
            // Check if alive
            if(mHealth <= 0) mWorld->RemoveObject(this);
        }
    }
}
