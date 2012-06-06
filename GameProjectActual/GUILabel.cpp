#include <string>
#include "GUILabel.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Default constructor. */
GUILabel::GUILabel() : mText(""), mFontWidth(9), mFontHeight(15)
{
}

/** Construct label with given text. */
GUILabel::GUILabel(const string& text) : mText(text), mFontWidth(9), mFontHeight(15)
{
}

/** Destructor. */
GUILabel::~GUILabel()
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Draw label by drawing text with a fixed font. */
void GUILabel::Draw()
{
	if (!mVisible) return;

	int w = (int)(mText.length() * mFontWidth);
	int h = mFontHeight;

	int align_x = 0;
	int align_y = 0;
	if (mHorizontalAlignment == GUIComponent::GUI_HALIGN_RIGHT) {
		align_x = -w;
	} else if (mHorizontalAlignment == GUIComponent::GUI_HALIGN_CENTER) {
		align_x = -w/2;
	}

	if (mVerticalAlignment == GUIComponent::GUI_VALIGN_TOP) {
		align_y = -h;
	} else if (mVerticalAlignment == GUIComponent::GUI_VALIGN_MIDDLE) {
		align_y = -h/2;
	}

	glDisable(GL_LIGHTING);
	glColor3f(mColor[0], mColor[1], mColor[2]);
	glRasterPos2i(mPosition.x + mBorder.x + align_x, mPosition.y + mBorder.y + align_y);
	for (uint i = 0; i < mText.length(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, mText[i]);
	}
	glEnable(GL_LIGHTING);
}
