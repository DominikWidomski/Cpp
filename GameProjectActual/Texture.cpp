#include "GameUtil.h"
#include "Image.h"
#include "Texture.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

Texture::Texture(Image* image)
{
	// Get a texture id from OpenGL
	GLuint textures[1];
	glGenTextures(1, &textures[0]);
	mTextureID = textures[0];
	mImageWidth = image->GetWidth();
	mImageHeight = image->GetHeight();

	// Bind a texture to an image using id
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mImageWidth, mImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->GetPixelData());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
}
