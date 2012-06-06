#ifndef __GUICOMPONENT_H__
#define __GUICOMPONENT_H__

#include "GameUtil.h"

class GUIComponent
{
public:
	enum GUIHorizontalAlignment
	{
		GUI_HALIGN_LEFT,
		GUI_HALIGN_CENTER,
		GUI_HALIGN_RIGHT,
	};

	enum GUIVerticalAlignment
	{
		GUI_VALIGN_TOP,
		GUI_VALIGN_MIDDLE,
		GUI_VALIGN_BOTTOM,
	};

public:
	GUIComponent();
	virtual ~GUIComponent();
	virtual void Draw();

	virtual GLVector2i GetPreferredSize() { return GLVector2i(0,0); }

	virtual void SetSize(const GLVector2i& size) { mSize = size; }
	GLVector2i GetSize() { return mSize; }

	virtual void SetPosition(const GLVector2i& position) { mPosition = position; }
	GLVector2i GetPosition() { return mPosition; }

	void SetHorizontalAlignment(GUIHorizontalAlignment halignment) { mHorizontalAlignment = halignment; }
	GUIHorizontalAlignment GetHorizontalAlignment() { return mHorizontalAlignment; }

	void SetVerticalAlignment(GUIVerticalAlignment valignment) { mVerticalAlignment = valignment; }
	GUIVerticalAlignment GetVerticalAlignment() { return mVerticalAlignment; }

	void SetBorder(const GLVector2i& border) { mBorder = border; }
	GLVector2i GetBorder() { return mBorder; }

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() { return mVisible; }

	void SetColor(const GLVector3f& color) { mColor = color; }
	GLVector3f GetColor() { return mColor; }
protected:
	GLVector2i mSize;
	GLVector2i mPosition;
	GLVector2i mBorder;
	GLVector3f mColor;
	bool mVisible;
	GUIHorizontalAlignment mHorizontalAlignment;
	GUIVerticalAlignment mVerticalAlignment;
};

#endif
