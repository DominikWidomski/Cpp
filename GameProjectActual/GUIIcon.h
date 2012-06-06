#ifndef __GUIICON_H__
#define __GUIICON_H__

#include "GUIComponent.h"

class Image;

class GUIIcon : public GUIComponent
{
public:
	GUIIcon();
	GUIIcon(Image* image);
	virtual ~GUIIcon();
	virtual void Draw();
	void SetImage(Image* i);
protected:
	Image* mImage;
};

#endif