#include "ImageManager.h"
#include "TextureManager.h"
#include "AnimationManager.h"
#include "Image.h"
#include "Texture.h"
#include "Animation.h"

Animation* AnimationManager::CreateAnimationFromRawRGB(const string& name, const uint width, const uint height, const uint frame_width, const uint frame_height, const string& rgb_filename)
{
	Image* image = ImageManager::GetInstance().CreateImageFromRawRGB(name, width, height, rgb_filename);
	return CreateAnimationFromImage(name, frame_width, frame_height, image);
}

Animation* AnimationManager::CreateAnimationFromRawRGBA(const string& name, const uint width, const uint height, const uint frame_width, const uint frame_height, const string& rgb_filename, const string& alpha_filename)
{
	Image* image = ImageManager::GetInstance().CreateImageFromRawRGBA(name, width, height, rgb_filename, alpha_filename);
	return CreateAnimationFromImage(name, frame_width, frame_height, image);
}

Animation* AnimationManager::CreateAnimationFromImage(const string& name, const uint frame_width, const uint frame_height, Image* image)
{
	uint num_frames = (image->GetWidth() / frame_width) * (image->GetHeight() / frame_height);
	uint* texture_ids = new uint[num_frames];
	uint current_frame = 0;
	for (uint i = 0; i < image->GetWidth(); i += frame_width) {
		for (uint j = 0; j < image->GetHeight(); j += frame_height) {
			std::ostringstream frame_stream;
			frame_stream << name << "-" << current_frame;
			std::string frame_name = frame_stream.str();

			Image* frame_image = ImageManager::GetInstance().CreateImageFromImage(frame_name, image, i, j, frame_width, frame_height);
			Texture* frame_texture = TextureManager::GetInstance().CreateTextureFromImage(frame_name, frame_image);
			texture_ids[current_frame++] = frame_texture->GetTextureID();
		}
	}
	Animation* animation = new Animation(frame_width, frame_height, texture_ids, num_frames);
	mAnimationMap.insert(NamedAnimationMap::value_type(name, animation));
	return animation;
}

Animation* AnimationManager::GetAnimationByName(const string& name)
{
	NamedAnimationMap::iterator it = mAnimationMap.find(name);
	return (it == mAnimationMap.end()) ? 0 : it->second;
}
