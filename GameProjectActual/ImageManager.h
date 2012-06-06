#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

#include "GameUtil.h"

class Image;

class ImageManager
{
public:
	inline static ImageManager& GetInstance(void)
	{
		static ImageManager mInstance;
		return mInstance;
	}

	Image* CreateImageFromRawRGB(const string& name, const uint width, const uint height, const string& rgb_filename);
	Image* CreateImageFromRawRGBA(const string& name, const uint width, const uint height, const string& rgb_filename, const string& alpha_filename);
	Image* CreateImageFromImage(const string& name, Image* image, const uint x, const uint y, const uint w, const uint h);
	Image* GetImageByName(const string& name);

private:
	ImageManager() {} // Private constructor
	~ImageManager() {} // Private destructor
	
	typedef map< string, Image* > NamedImageMap;
	NamedImageMap mImageMap;
};

#endif