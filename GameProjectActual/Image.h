#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "GameUtil.h"

using namespace std;

class Image
{
public:
	Image();
	Image(uint width, uint height);
	Image(uint width, uint height, const string& rgb_filename);
	Image(uint width, uint height, const string& rgb_filename, const string& alpha_filename);
	Image(Image* image, const uint x, const uint y, const uint w, const uint h);
	~Image();

	void SetTransparentColour(uchar r, uchar g, uchar b);

	uint GetWidth() const { return mWidth; };
	uint GetHeight() const { return mHeight; };
	uint GetNumPixels() const { return mNumPixels; };
	uchar* GetPixelData() const { return mPixelData; };

private:
	void LoadRawRGB(const string& rgb_filename);
	void LoadRawAlpha(const string& alpha_filename);

	uint mWidth;
	uint mHeight;
	uint mNumPixels;
	uchar* mPixelData;
};

#endif