#ifndef __IWINDOWLISTENER_H__
#define __IWINDOWLISTENER_H__

class IWindowListener
{
public:
	virtual void OnWindowReshaped(int w, int h);
	virtual void OnWindowVisible(int visibility);
};

#endif
