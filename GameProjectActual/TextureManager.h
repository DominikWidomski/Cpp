#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include "GameUtil.h"

class Image;
class Texture;

class TextureManager
{
public:
	inline static TextureManager& GetInstance(void)
	{
		static TextureManager mInstance;
		return mInstance;
	}

	Texture* CreateTextureFromRawRGB(const string& n, const uint w, const uint h, const string& rgb_filename);
	Texture* CreateTextureFromRawRGBA(const string& n, const uint w, const uint h, const string& rgb_filename, const string& alpha_filename);
	Texture* CreateTextureFromImage(const string& name, Image* image);
	Texture* GetTextureByName(const string& name);

private:
	TextureManager() {} // Private constructor
	~TextureManager() {} // Private destructor
	
	typedef map< string, Texture* > NamedTextureMap;
	NamedTextureMap mTextureMap;
};

#endif