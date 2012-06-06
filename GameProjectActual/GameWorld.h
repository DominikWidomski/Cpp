#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "GameUtil.h"
#include "IGameWorldListener.h"
#include "UnitManager.h"
#include "GUISelectionBox.h"

class GameObject;
class Order;

// Define a type of list to hold game objects
typedef list< SmartPtr< GameObject > > GameObjectList;

// Define a type of map to hold lists of collisions
typedef map< SmartPtr<GameObject>, GameObjectList > CollisionMap;

class GameWorld
{
public:
	GameWorld(void);
	GameWorld(int x, int y);
	~GameWorld(void);

	void Update(int t);
	void Render(void);

	void AssignOrderToSelected(SmartPtr<Order> order);
	SmartPtr<GameObject> GetOnClickSelect(GLVector3f w);

//    void AddInteractingObject( SmartPtr<GameObject> ptr);
	void AddObject( SmartPtr<GameObject> ptr );
	void RemoveObject( SmartPtr<GameObject> ptr );
	void RemoveObject( GameObject* ptr );
	// SmartPtr<GameObject> GetGameObject( string name );
	void AddUnitTeam1( SmartPtr<GameObject> ptr);
	void AddUnitTeam2( SmartPtr<GameObject> ptr);

	GameObjectList GetCollisions( SmartPtr<GameObject> ptr );
	GameObjectList GetCollisions( GameObject* optr );

	void AddListener( IGameWorldListener* lptr) { mListeners.push_back(lptr); }
	void RemoveListener( IGameWorldListener* lptr) { mListeners.remove(lptr); }

	void FireWorldUpdated();
	void FireObjectAdded( SmartPtr<GameObject> ptr );
	void FireObjectRemoved( SmartPtr<GameObject> ptr );

    void GiveSelectionBox(SmartPtr<GUISelectionBox> sb) { mSelectionBox = sb; }
	void GiveCameraFocus(SmartPtr<GLVector3f> cf) { mCameraFocus = cf; }

	void SetWidth(int w) { mWidth = w; }
	int GetWidth() { return mWidth; }

	void SetHeight(int h) { mHeight = h; }
	int GetHeight() { return mHeight; }

	void WrapXY(float &x, float &y);

protected:
	void UpdateObjects(int t);
	void UpdateCollisions(int t);

	SmartPtr<GLVector3f> mCameraFocus;
	// TODO implementation of CheckDead() to check all the dead GameObjects and remove them.
//	void CheckDead();

    // Create the Unit Manager to store units
//    UnitManager mUnitManager;
	// Create a list of ALL named game objects
	GameObjectList mGameObjects;
	// Create a list of named game objects that will interact
//    GameObjectList mInteractingGameObjects;
	// Create a map of colliding game objects
	CollisionMap mCollisions;

	// Define a type of list to hold game world listeners
	typedef list< IGameWorldListener* > GameWorldListenerList;
	// Create a list of game world listeners
	GameWorldListenerList mListeners;

	SmartPtr<GUISelectionBox> mSelectionBox;

	// The width of the world
	int mWidth;
	// The height of the world
	int mHeight;
};

#endif
