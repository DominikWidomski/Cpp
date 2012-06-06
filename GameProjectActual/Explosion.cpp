#include "GameWorld.h"
#include "BoundingSphere.h"
#include "Explosion.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Constructor. */
Explosion::Explosion() : GameObject("Explosion") {}

/** Construct a new explosion with given position, velocity, angle and rotation. */
Explosion::Explosion(GLVector3f p, GLVector3f v, GLfloat h, GLfloat r)
	: GameObject("Explosion", p, v, GLVector3f(), h, r) {}

/** Copy constructor. */
Explosion::Explosion(const Explosion& e) : GameObject(e) {}

/** Destructor. */
Explosion::~Explosion(void) {}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update explosion, removing it from game world if necessary. */
void Explosion::Update(int t)
{
	// Update position/velocity
	GameObject::Update(t);

	if (mSprite.GetPtr() == NULL) return;

	// If sprite has finished animation remove explosion from world
	if (!mSprite->IsAnimating()) { 
		if (mWorld) mWorld->RemoveObject(this);
	}
}

