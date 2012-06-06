#include "GameUtil.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "Drone.h"



// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////



/** Default constructor. */

GameWorld::GameWorld(void) : mWidth(800), mHeight(600)
{
}

GameWorld::GameWorld(int w, int h) : mWidth(w), mHeight(h)
{
}


/** Destructor. */

GameWorld::~GameWorld(void)
{
}



// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////



/** Update the world. */

void GameWorld::Update(int t)

{

	UpdateObjects(t);
	UpdateCollisions(t);

	// Send update message to listeners

	FireWorldUpdated();

}



/** Render the world by rendering all of its objects. */

void GameWorld::Render(void)
{
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glClearDepth(1.0);
//    glDepthFunc(GL_LESS);
//    glEnable(GL_DEPTH_TEST);
//    glShadeModel(GL_SMOOTH);
	// Update the projection matrix
	glMatrixMode(GL_PROJECTION);
	// Store the current projection matrix
	glPushMatrix();
	// Initialize the projection matrix to the identity matrix
	glLoadIdentity();
	// Set orthographic projection to include the world
//	glOrtho(-mWidth/2, mWidth/2, -mHeight/2, mHeight/2, -100, 100);
	glOrtho(mCameraFocus->x - mWidth/2, mCameraFocus->x + mWidth/2, mCameraFocus->y - mHeight/2, mCameraFocus->y + mHeight/2, -100, 100);
//    gluPerspective(40.0, mWidth/mHeight, -100, 100);
	// Switch to model mode ready for rendering
	glMatrixMode(GL_MODELVIEW);
	// Initialize the projection matrix to the identity matrix
	glLoadIdentity();
	// lighting
	// lighting arrays
//    float lightambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
//    float lightdiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
//    float lightposition[] = {0.0f, 0.0f, 2.0f, 1.0f};
//    glLightfv(GL_LIGHT1, GL_AMBIENT, lightambient); // set up ambient light
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightdiffuse); // diffuse lighting
//    glLightfv(GL_LIGHT1, GL_POSITION, lightposition); // light position
    glEnable(GL_LIGHT1);
	// Render every object in the world
	for (GameObjectList::iterator it = mGameObjects.begin(); it != mGameObjects.end(); ++it) {
		(*it)->PreRender();
		(*it)->Render();
		(*it)->PostRender();
	}
}

///** Add a game object to the world. */
//void GameWorld::AddInteractingObject(SmartPtr<GameObject> ptr)
//{
//    // Add game object to the list of interacting objects
//    mInteractingGameObjects.push_back(ptr);
//    // Add game object to collision map
//	mCollisions[ptr] = GameObjectList();
//	AddObject(ptr);
//}

/** Add a game object to the world. */
void GameWorld::AddObject(SmartPtr<GameObject> ptr)
{
	// Add game object
	mGameObjects.push_back(ptr);

    // Add game object to collision map
	mCollisions[ptr] = GameObjectList();

	// Add reference to this world
	ptr->SetWorld(this);

	// Send message to all listeners
	FireObjectAdded(ptr);
}

/** Remove a game object from the world. */
void GameWorld::RemoveObject(GameObject* ptr)
{
	RemoveObject(SmartPtr<GameObject>(ptr));
}

/** Remove a game object from the world. */
void GameWorld::RemoveObject(SmartPtr<GameObject> ptr)
{
	// Remove the game object from the list
//	mInteractingGameObjects.remove(ptr);
    mGameObjects.remove(ptr);

	// Remove game object from collision map
	mCollisions.erase(ptr);

	// Remove reference to this world
	//ptr->SetWorld(NULL);

	// Send message to all listeners
	FireObjectRemoved(ptr);
}

/** Inform all listeners of world update. */
void GameWorld::FireWorldUpdated()
{
	// Send update message to all listeners

	for (GameWorldListenerList::iterator it = mListeners.begin(); it != mListeners.end(); ++it) {

		(*it)->OnWorldUpdated(this);

	}

}

/** Inform all listeners of object addition. */
void GameWorld::FireObjectAdded(SmartPtr<GameObject> ptr)
{
	// Send message to all listeners

	for (GameWorldListenerList::iterator it = mListeners.begin(); it != mListeners.end(); ++it) {

		(*it)->OnObjectAdded(this, ptr);

	}

}

/** Inform all listeners of object removal. */
void GameWorld::FireObjectRemoved(SmartPtr<GameObject> ptr)
{
	// Send message to all listeners

	for (GameWorldListenerList::iterator lit = mListeners.begin(); lit != mListeners.end(); ++lit) {

		(*lit)->OnObjectRemoved(this, ptr);

	}

}

/** Get all the collisions for a given object. */
GameObjectList GameWorld::GetCollisions(SmartPtr<GameObject> ptr)
{
	// Find the named game object
	CollisionMap::iterator it = mCollisions.find(ptr);
	// If object does not exist return empty list
	if (it == mCollisions.end()) {
		mCollisions[ptr] = GameObjectList();
		CollisionMap::iterator it2 = mCollisions.find(ptr);
		return it2->second;
	}
	// Otherwise return list from collision map
	return it->second;
}

/** Get all the collisions for a given object. */
GameObjectList GameWorld::GetCollisions(GameObject* optr)
{
	return GetCollisions(SmartPtr<GameObject>(optr));
}


/** Give an order to all selected GameObjects */
void GameWorld::AssignOrderToSelected(SmartPtr<Order> order)
{
    GameObjectList::iterator it = mGameObjects.begin();

    while(it != mGameObjects.end()) {
        GameObjectList::iterator copy_it = it++;
        if( (*copy_it)->IsSelected() ){
            if( (*copy_it)->GetType() == GameObjectType("Drone")){
                Drone* d = (Drone*) copy_it->GetPtr();
                d->AssignOrder(order);
                cout    << "assigning an order of type: "
                        << order->GetType()
                        << "for object of type: Drone"
                        << order->GetDestination().x << order->GetDestination().y
                        << endl;
            }
        }
    }
}

/** Check for GameObjects that are selected with a mouse click, used for single click selection as well as ordering
*   Returns the first object it finds.
* @param x, y : pass World coordinates
*/
SmartPtr<GameObject> GameWorld::GetOnClickSelect(GLVector3f w)
{
    GameObjectList::iterator it = mGameObjects.begin();
    GameObjectList::iterator copy_it;

    cout << "Checking OnClick Select\n";

    while(it != mGameObjects.end()) {
        copy_it = it++;

        GameObjectType gt = (*copy_it)->GetType();

        if((*copy_it)->SelectionTest(w)){
            return SmartPtr<GameObject>(*copy_it);
        }
    }
    return NULL;
}

/** Update all objects. */
void GameWorld::UpdateObjects(int t)
{

	// Update every object in the world

	GameObjectList::iterator it = mGameObjects.begin();

    int i = 0;
    SmartPtr<GameObject> go = (*it);
    GameObjectType typeName = (*it)->GetType();

    GameObjectList::iterator copy_it;
	while (it != mGameObjects.end()) {

		// We have to be careful and make a copy of the iterator
		// before calling Update() in case the object removes itself
		//GameObjectList::iterator copy_it = it++;
		copy_it = it++;

		// If selection box exists and is visible (i.e. active) check for selection
		if(mSelectionBox.GetPtr() != NULL && mSelectionBox->GetVisible())
		if((*copy_it)->GetType() == GameObjectType("Drone")){
            if(mSelectionBox->CheckUnitWithin((*copy_it))){
                (*copy_it)->MakeSelected();
            } else {
                (*copy_it)->MakeUnselected();
            }
		}

		(*copy_it)->Update(t);
		i++;
		//it++;
		//(*it)->Update(t);
	}
}

/** Update all collisions. */

void GameWorld::UpdateCollisions(int t)
{
	CollisionMap::iterator it1;
	CollisionMap::iterator it2;

	// Clear collisions
	for (it1 = mCollisions.begin(); it1 != mCollisions.end(); ++it1) {
		GameObjectList& collisions = it1->second;
		collisions.clear();
	}

	// Update collisions
	for (it1 = mCollisions.begin(); it1 != mCollisions.end(); ++it1) {
		SmartPtr<GameObject> object1 = it1->first;
		GameObjectList& collisions1 = it1->second;
		for (it2 = mCollisions.begin(); it2 != mCollisions.end(); ++it2) {
			SmartPtr<GameObject> object2 = it2->first;
			GameObjectList& collisions2 = it2->second;
			if (object2 != object1) {
				if (object1->CollisionTest(object2)) {
					collisions1.push_back(object2);
				}
			}
		}
	}

	// Call objects to handle collisions
	it1 = mCollisions.begin();
	while (it1 != mCollisions.end()) {
		// We have to be careful and make a copy of the iterator
		// before calling OnCollision() in case the object removes itself
		it2 = it1++;
		SmartPtr<GameObject> object = it2->first;
		GameObjectList collisions = it2->second;
		if (!collisions.empty()) object->OnCollision(collisions);
	}
}


/** Utility method to wrap positions around the world's edges. */

void GameWorld::WrapXY(GLfloat &x, GLfloat &y)

{

//    cout << "wrap to: " << mWidth << " " << mHeight << endl;
//	// Wrap x and y coords that are out of the bounds of the world
//
//	while (x >  mWidth/2)  x -= mWidth;
//
//	while (y >  mHeight/2) y -= mHeight;
//
//	while (x < -mWidth/2)  x += mWidth;
//
//	while (y < -mHeight/2) y += mHeight;

}
