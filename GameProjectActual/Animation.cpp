#include "GameUtil.h"
#include "Texture.h"
#include "Animation.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

Animation::Animation(uint width, uint height, uint* frame_ids, uint num_frames)
	: mWidth(width), mHeight(height), mFrameIDs(frame_ids), mNumFrames(num_frames)
{
}

Animation::~Animation()
{
}
