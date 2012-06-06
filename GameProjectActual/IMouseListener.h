#ifndef __IMOUSELISTENER_H__
#define __IMOUSELISTENER_H__

class IMouseListener
{
public:
	virtual void OnMouseDragged(int x, int y) = 0;
	virtual void OnMouseButton(int button, int state, int x, int y) = 0;
	virtual void OnMouseMoved(int x, int y) = 0;
};

#endif
