#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "GameUtil.h"

// class Texture;
class Animation;

class Sprite
{
public:
 	// Sprite(int w, int h, int f, Texture* t, bool l = true);
 	Sprite(uint w, uint h, Animation* a, bool l = true);
	virtual ~Sprite();

	virtual void Update(int t);
	virtual void Render(void);

	void SetCurrentFrame(int f) { mCurrentFrame = f % mFrames; }
	int GetCurrentFrame() { return mCurrentFrame; }

	void SetLoopAnimation(bool loop) { mLoopAnimation = loop; }
	bool GetLoopAnimation() { return mLoopAnimation; }

	bool IsAnimating() { return mAnimating; }

private:
	int mWidth;
	int mHeight;
	int mOffsetX;
	int mOffsetY;

	int mFrames;
	int mCurrentFrame;
	bool mLoopAnimation;
	bool mAnimating;

	// Texture* mTexture;
	Animation* mAnimation;
	
	int mFrameMillis;
	int mMillisPerFrame;
};

#endif