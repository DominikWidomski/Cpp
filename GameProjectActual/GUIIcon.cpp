#include "Image.h"
#include "GUIIcon.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Default constructor. */
GUIIcon::GUIIcon()
{
	SetImage(NULL);
}

/** Construct an icon with given image. */
GUIIcon::GUIIcon(Image* image)
{
	SetImage(image);
}

/** Destructor. */
GUIIcon::~GUIIcon()
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Draw icon by drawing image. */
void GUIIcon::Draw()
{
	if (!mVisible) return;
	if (mImage == NULL) return;
	glAlphaFunc(GL_GEQUAL, 0.5);
	glEnable(GL_ALPHA_TEST);
	glDrawBuffer(GL_BACK);
	glRasterPos2i(mPosition.x + mBorder.x, mPosition.y + mBorder.y);
	glDrawPixels(mImage->GetWidth(), mImage->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, mImage->GetPixelData());
	glDisable(GL_ALPHA_TEST);
}

/** Set the image drawn by this icon. */
void GUIIcon::SetImage(Image* image)
{
	mImage = image;
}
