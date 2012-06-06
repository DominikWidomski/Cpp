#ifndef __GAMESESSION_H__
#define __GAMESESSION_H__

#include "ITimerListener.h"

class GameWorld;
class GameDisplay;
class GameWindow;
class GameObject;

class GameSession : public ITimerListener
{
public:
	GameSession(int argc, char* argv[]);
	~GameSession(void);

	virtual void OnTimer(int value) {}

    void CameraMoveLeft()   { mCameraFocus->x -= 2; }
    void CameraMoveRight()  { mCameraFocus->x += 2; }
    void CameraMoveUp()     { mCameraFocus->y += 2; }
    void CameraMoveDown()   { mCameraFocus->y -= 2; }
    void PutFocusOn(SmartPtr<GameObject> object);
    void MoveFocusTo(GLVector3f fc) { (*mCameraFocus) = fc; }

	virtual void Start(void);
	virtual void Stop(void);

protected:
	GameWorld* mGameWorld;
	GameDisplay* mGameDisplay;
	GameWindow* mGameWindow;

    // TODO camera
	SmartPtr<GLVector3f> mCameraFocus;
    bool mMoveCamera;

	void SetTimer(uint msecs, int value);
};

#endif
