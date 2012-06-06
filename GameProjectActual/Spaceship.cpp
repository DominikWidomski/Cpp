#include "GameUtil.h"
#include "GameWorld.h"
#include "BoundingSphere.h"
#include "Bullet.h"
#include "Spaceship.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
Spaceship::Spaceship()
	: GameObject("Spaceship"), mThrust(0)
{
	mBoundingShape = new BoundingSphere(this, 4);

	mFireTimer = 0;
    mFireReloadTime = 1000.0;
    mHealth = 100.0;
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
Spaceship::Spaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Spaceship", p, v, a, h, r), mThrust(0)
{
	mBoundingShape = new BoundingSphere(this, 4);

	mFireTimer = 0;
    mFireReloadTime = 1000.0;
    mHealth = 100.0;
}

/** Copy constructor. */
Spaceship::Spaceship(const Spaceship& s)
	: GameObject(s), mThrust(0)
{
	mBoundingShape = new BoundingSphere(this, 4);

	mFireTimer = 0;
    mFireReloadTime = 1000.0;
    mHealth = 100.0;
}

/** Destructor. */
Spaceship::~Spaceship(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this spaceship. */
void Spaceship::Update(int t)
{
    /*
    * @todo rethink this thing... use already made methods instead of pos.x = this.x, pos.y = this.y etc...
    */
	float dt = t / 1000.0f;

	// Update angle
	AddAngle(mRotation * dt);

    // Update Acceleration
    mAcceleration.x = mThrust*cos(DEG2RAD*mAngle);
    mAcceleration.y = mThrust*sin(DEG2RAD*mAngle);
    // Update Velocity
//	mVelocity.x += mAcceleration.x * dt;
//	mVelocity.y += mAcceleration.y * dt;
//    mVelocity.z += mAcceleration.z * dt;
    // Update Position
    mPosition.x += mAcceleration.x * dt;
    mPosition.y += mAcceleration.y * dt;
//    mPosition.z += mVelocity.z * dt;
    // Reset acceleration to 0
	mAcceleration = GLVector3f(0,0,0);
//	mVelocity = GLVector3f(0,0,0);


    if(mFireTimer > 0) mFireTimer -= t;

	// Update sprite if one exists
	if (mSprite.GetPtr() != NULL) mSprite->Update(t);
	// If in world, wrap position
	if (mWorld) { mWorld->WrapXY(mPosition.x, mPosition.y); }
}

/** Render this spaceship. */
void Spaceship::Render(void)
{
	if (mSpaceshipShape.GetPtr() != NULL) mSpaceshipShape->Render();

	// If ship is thrusting
	if ((mThrust > 0) && (mThrusterShape.GetPtr() != NULL)) {
		mThrusterShape->Render();
	}

	// Call base class to render debug graphics if required
	GameObject::Render();
}

/** Fire the rockets. */
void Spaceship::Thrust(float t)
{
	mThrust = t;
	// Increase acceleration in the direction of ship
	mAcceleration.x = mThrust*cos(DEG2RAD*mAngle);
	mAcceleration.y = mThrust*sin(DEG2RAD*mAngle);
}

/** Set the rotation. */
void Spaceship::Rotate(float r)
{
	mRotation = r;
}

/** Shoot a bullet. */
void Spaceship::Shoot(void)
{
    // check if is able to fire
    if (mFireTimer > 0) return;
	// Check the world exists
	if (!mWorld) return;
	// Construct a unit length vector in the direction the spaceship is headed
	GLVector3f spaceship_heading(cos(DEG2RAD*mAngle), sin(DEG2RAD*mAngle), 0);
	spaceship_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f bullet_position = mPosition + (spaceship_heading * 4);
	// Calculate how fast the bullet should travel
	float bullet_speed = 51 + mVelocity.dot(spaceship_heading);
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + spaceship_heading * bullet_speed;
	// Construct a new bullet
	SmartPtr<GameObject> bullet =
		new Bullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000);
	bullet->SetShape(mBulletShape);
	// Add the new bullet to the game world
	mWorld->AddObject(bullet);

    mFireTimer = mFireReloadTime;

    cout << "RELOADING =============== FIRE TIMER: " << mFireTimer << endl;
}

bool Spaceship::CollisionTest(SmartPtr<GameObject> o)
{
//	if (o->GetType() != GameObjectType("Asteroid")) return false;
	if (o->GetType() == GameObjectType("Drone")) return false;
	if (mBoundingShape.GetPtr() == NULL) return false;
	if (o->GetBoundingShape().GetPtr() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Spaceship::OnCollision(const GameObjectList &objects)
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
        if((*type) == GameObjectType("Asteroid"))
        {
//            mWorld->RemoveObject(this);
        }
    }
}
