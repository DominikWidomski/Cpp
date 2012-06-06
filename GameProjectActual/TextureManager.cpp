#include "ImageManager.h"
#include "TextureManager.h"
#include "Image.h"
#include "Texture.h"

Texture* TextureManager::CreateTextureFromRawRGB(const string& name, const uint width, const uint height, const string& rgb_filename)
{
	Image* image = ImageManager::GetInstance().CreateImageFromRawRGB(name, width, height, rgb_filename);
	return CreateTextureFromImage(name, image);
}

Texture* TextureManager::CreateTextureFromRawRGBA(const string& name, const uint width, const uint height, const string& rgb_filename, const string& alpha_filename)
{
	Image* image = ImageManager::GetInstance().CreateImageFromRawRGBA(name, width, height, rgb_filename, alpha_filename);
	return CreateTextureFromImage(name, image);
}

Texture* TextureManager::CreateTextureFromImage(const string& name, Image* image)
{
	Texture* texture = new Texture(image);
	mTextureMap.insert(NamedTextureMap::value_type(name, texture));
	return texture;
}

Texture* TextureManager::GetTextureByName(const string& name)
{
	NamedTextureMap::iterator it = mTextureMap.find(name);
	return (it == mTextureMap.end()) ? 0 : it->second;
}