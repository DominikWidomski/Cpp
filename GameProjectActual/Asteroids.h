#ifndef __ASTEROIDS_H__
#define __ASTEROIDS_H__

#include "GameUtil.h"
#include "GameSession.h"
#include "IKeyboardListener.h"
#include "IMouseListener.h"
#include "IPlayerListener.h"
#include "IScoreListener.h"
#include "Player.h"
#include "ScoreKeeper.h"

#include "UnitManager.h"

class GameObject;
class GUILabel;
class GUISelectionBox;
class Shape;
class Spaceship;

typedef map< string, SmartPtr< Shape > > ShapesMap;

class Asteroids : public GameSession, IKeyboardListener, IMouseListener, IScoreListener, IGameWorldListener, IPlayerListener
{
public:
	Asteroids(int argc, char *argv[]);
	virtual ~Asteroids(void);

	virtual void Start(void);
	virtual void Stop(void);

    // Declaration of IMouseListener interface //////////////////////////////////
    void OnMouseDragged(int x, int y);
	void OnMouseButton(int button, int state, int x, int y);
	void OnMouseMoved(int x, int y);

	// Declaration of IKeyboardListener interface ///////////////////////////////
	void OnKeyPressed(uchar key, int x, int y);
	void OnKeyReleased(uchar key, int x, int y);
	void OnSpecialKeyPressed(int key, int x, int y);
	void OnSpecialKeyReleased(int key, int x, int y);

	// Declaration of IScoreListener interface //////////////////////////////////

	void OnScoreChanged(int score);

	// Declaration of IGameWorldListener interface //////////////////////////////

	void OnWorldUpdated(GameWorld* world) {}
	void OnObjectAdded(GameWorld* world, SmartPtr<GameObject> object) {}
	void OnObjectRemoved(GameWorld* world, SmartPtr<GameObject> object);

	// Declaration of IPlayerListener interface /////////////////////////////////

	void OnPlayerKilled(int lives_left);

	// Override the default implementation of ITimerListener ////////////////////

	void OnTimer(int value);

private:
	Player mPlayer;
	ScoreKeeper mScoreKeeper;
	SmartPtr<Spaceship> mSpaceship;

	SmartPtr<GUILabel> mScoreLabel;
	SmartPtr<GUILabel> mLivesLabel;
	SmartPtr<GUILabel> mGameOverLabel;
	SmartPtr<GUISelectionBox> mSelectionBox;

	SmartPtr<Shape> mSelectedShape;

	uint mLevel;
	uint mAsteroidCount;

	void CreateGUI();

	void ResetSpaceship();
	SmartPtr<GameObject> CreateSpaceship();
	SmartPtr<GameObject> CreateAsteroid();
	SmartPtr<GameObject> CreateAsteroid(int x, int y);      //enables creation of asteroids at a specific location
	SmartPtr<GameObject> CreateAsteroidOre(int x, int y);      //enables creation of ore asteroids at a specific location
	SmartPtr<GameObject> CreateOre();
	SmartPtr<GameObject> CreateOre(int x, int y);
	SmartPtr<GameObject> CreateDrone(int x, int y);
	SmartPtr<GameObject> CreateExplosion();

//	SmartPtr<Order> CreateOrder(SmartPtr<GameObject> checkSelect);
	// void CreateLevel(uint level, uint num_asteroids);

	const static uint SHOW_GAME_OVER = 0;
	const static uint START_NEXT_LEVEL = 1;
	const static uint CREATE_NEW_PLAYER = 2;

	static bool mConsoleDebug;
};

#endif
