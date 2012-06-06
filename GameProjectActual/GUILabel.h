#ifndef __GUILABEL_H__
#define __GUILABEL_H__

#include "GameUtil.h"
#include "GUIComponent.h"

class GUILabel : public GUIComponent
{
public:
	GUILabel();
	GUILabel(const string& t);
	virtual ~GUILabel();
	virtual void Draw();
	void SetText(const string& text) { mText = text; }
protected:
	string mText;
	int mFontWidth;
	int mFontHeight;
};

#endif