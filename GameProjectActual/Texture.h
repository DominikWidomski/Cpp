#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class Image;

class Texture
{
public:
	Texture(Image* image);
	~Texture();
	uint GetTextureID() const { return mTextureID; }
	uint GetImageWidth() const { return mImageWidth; }
	uint GetImageHeight() const { return mImageHeight; }
private:
	uint mTextureID;
	uint mImageWidth;
	uint mImageHeight;
};

#endif