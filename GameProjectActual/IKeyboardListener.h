#ifndef __IKEYBOARDLISTENER_H__
#define __IKEYBOARDLISTENER_H__

typedef unsigned char uchar;

class IKeyboardListener
{
public:
	virtual void OnKeyPressed(uchar key, int x, int y) = 0;
	virtual void OnKeyReleased(uchar key, int x, int y) = 0;
	virtual void OnSpecialKeyPressed(int key, int x, int y) = 0;
	virtual void OnSpecialKeyReleased(int key, int x, int y) = 0;
};

#endif