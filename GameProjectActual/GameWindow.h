#ifndef __GAMEWINDOW_H__
#define __GAMEWINDOW_H__

#include "GameUtil.h"
#include "GlutWindow.h"
//#include "IKeyboardListener.h"

class GameWorld;
class GameDisplay;

class GameWindow : public GlutWindow
{
public:
	GameWindow(int w, int h, int x, int y, char* t);
	virtual ~GameWindow();

	virtual void OnDisplay(void);
	virtual void OnIdle(void);
	virtual void OnWindowReshaped(int w, int h);

	void UpdateWorldSize(void);
	void UpdateDisplaySize(void);

	void SetWorld(GameWorld* w);
	GameWorld* GetWorld();
	static int GetZoomLevel() { return ZOOM_LEVEL; }

	void SetDisplay(GameDisplay* w);
	GameDisplay* GetDisplay();

protected:
	static const int ZOOM_LEVEL;

	GameWorld* mWorld;
	GameDisplay* mDisplay;
};

#endif
