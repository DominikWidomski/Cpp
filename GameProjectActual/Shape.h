#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "GameUtil.h"

using namespace std;

typedef list< SmartPtr<GLVector3f> > GLVector3fList;

class Shape
{
public:
	Shape();
	Shape(const string& shape_filename);
	virtual ~Shape();

	void Render(void);

	void LoadShape(const string& shape_filename);

	const GLVector4f& GetRGBColour() { return mRGBA; }
	const GLVector3fList& GetPoints() { return mPoints; }

private:
	bool mLoop;
	GLenum mMode;
	GLVector4f mRGBA;
	GLVector3fList mPoints;
};

#endif
