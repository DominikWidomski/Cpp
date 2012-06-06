#ifndef __ANIMATION_H__
#define __ANIMATION_H__

class Image;

class Animation
{
public:
	Animation(uint width, uint height, uint* frame_ids, uint num_frames);
	~Animation();
	uint GetWidth() { return mWidth; }
	uint GetHeight() { return mHeight; }
	uint GetFrameTextureID(uint n) const { return mFrameIDs[n]; }
	uint GetNumFrames() const { return mNumFrames; }
private:
	uint mWidth;
	uint mHeight;
	uint* mFrameIDs;
	uint mNumFrames;
};

#endif