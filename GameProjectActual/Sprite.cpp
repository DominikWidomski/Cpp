#include "GameUtil.h"
#include "GameWindow.h"
#include "GameWorld.h"
#include "Texture.h"
#include "Animation.h"
#include "Sprite.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/*
Sprite::Sprite(int w, int h, int f, Texture* t, bool l)
	: mWidth(w),
	  mHeight(h),
	  mOffsetX(w/2),
	  mOffsetY(h/2),
	  mFrames(f),
	  mCurrentFrame(0),
	  mTexture(t),
	  mLoopAnimation(l),
	  mAnimating(true),
	  mFrameMillis(0),
	  mMillisPerFrame(1000/12)
{
}
*/

Sprite::Sprite(uint w, uint h, Animation* a, bool l)
	: mWidth(w),
	  mHeight(h),
	  mOffsetX(w/2),
	  mOffsetY(h/2),
	  mFrames(a->GetNumFrames()),
	  mAnimation(a),
	  mLoopAnimation(l),
	  mCurrentFrame(0),
	  mAnimating(true),
	  mFrameMillis(0),
	  mMillisPerFrame(1000/12)
{
}

Sprite::~Sprite()
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

void Sprite::Update(int t)
{
	mFrameMillis += t;
	if (mFrameMillis >= mMillisPerFrame) {
		mFrameMillis = mFrameMillis % mMillisPerFrame;

		mCurrentFrame++;
		if (mCurrentFrame >= mFrames) {
			if (mLoopAnimation) {
				mCurrentFrame = mCurrentFrame % mFrames;
			} else {
				mCurrentFrame = 0;
				mAnimating = false;
			}
		}
	}
}

/*
void Sprite::Render()
{
	float f1 = (float)mCurrentFrame / (float)mFrames;
	float f2 = (float)(mCurrentFrame+1) / (float)mFrames;
	float x1 = (float)(-mOffsetX);
	float y1 = (float)(-mOffsetY);
	float x2 = (float)(mWidth - mOffsetX);
	float y2 = (float)(mHeight - mOffsetY);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, f1); glVertex3f(x1, y1, 0.0f);
		glTexCoord2f(1.0f, f1); glVertex3f(x2, y1, 0.0f);
		glTexCoord2f(1.0f, f2); glVertex3f(x2, y2, 0.0f);
		glTexCoord2f(0.0f, f2); glVertex3f(x1, y2, 0.0f);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
*/

void Sprite::Render()
{
	float x1 = (float)(-mOffsetX);
	float y1 = (float)(-mOffsetY);
	float x2 = (float)(mWidth - mOffsetX);
	float y2 = (float)(mHeight - mOffsetY);

	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mAnimation->GetFrameTextureID(mCurrentFrame));
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y1, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y2, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y2, 0.0f);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
