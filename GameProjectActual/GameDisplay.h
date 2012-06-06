#ifndef __GAMEDISPLAY_H__
#define __GAMEDISPLAY_H__

#include "GameUtil.h"
#include "GUIContainer.h"

class GameDisplay
{
public:
	GameDisplay(void);
	GameDisplay(int w, int h);
	virtual ~GameDisplay(void);

	virtual void Update(int t) {}
	virtual void Render(void);

	void Reshape(int w, int h)
	{
		mWidth = w;
		mHeight = h;
		mContainer.SetSize(GLVector2i(mWidth, mHeight));
	}

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

	GUIContainer *GetContainer() { return &mContainer; }

protected:
	int mWidth;
	int mHeight;
	
	GUIContainer mContainer;
};

#endif