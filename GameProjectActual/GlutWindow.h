#ifndef __GLUTWINDOW_H__
#define __GLUTWINDOW_H__

#include "GameUtil.h"

typedef unsigned int uint;

class IKeyboardListener;
class IMouseListener;
class IWindowListener;

class GlutWindow
{
public:
	GlutWindow(int w, int h, int x, int y, char* title);
	~GlutWindow(void);

	virtual void OnDisplay(void);
	virtual void OnIdle(void);
	virtual void OnTimer(int value);
	virtual void OnKeyPressed(uchar key, int x, int y);
	virtual void OnKeyReleased(uchar key, int x, int y);
	virtual void OnSpecialKeyPressed(int key, int x, int y);
	virtual void OnSpecialKeyReleased(int key, int x, int y);
	virtual void OnMouseDragged(int x, int y);
	virtual void OnMouseButton(int button, int state, int x, int y);
	virtual void OnMouseMoved(int x, int y);
	virtual void OnWindowReshaped(int w, int h);
	virtual void OnWindowVisible(int visibility);

	int  GetWindowID(void);
	void SetFullscreen(bool fs);
	void SetTimer(uint msecs, int value);

	void AddKeyboardListener(SmartPtr<IKeyboardListener> lptr) { mKeyboardListeners.push_back(lptr); }
	void RemoveKeyboardListener(SmartPtr<IKeyboardListener> lptr) { mKeyboardListeners.remove(lptr); }

	void AddMouseListener(SmartPtr<IMouseListener> lptr) { mMouseListeners.push_back(lptr); }
	void RemoveMouseListener(SmartPtr<IMouseListener> lptr) { mMouseListeners.remove(lptr); }

	void AddWindowListener(SmartPtr<IWindowListener> lptr) { mWindowListeners.push_back(lptr); }
	void RemoveWindowListener(SmartPtr<IWindowListener> lptr) { mWindowListeners.remove(lptr); }

protected:
	int mWindowID;
	int mWidth;
	int mHeight;
	int mXCoord;
	int mYCoord;
	bool mFullscreen;

	typedef list< SmartPtr<IKeyboardListener> > KeyboardListenerList;
	KeyboardListenerList mKeyboardListeners;
	
	typedef list< SmartPtr<IMouseListener> > MouseListenerList;
	MouseListenerList mMouseListeners;
	
	typedef list< SmartPtr<IWindowListener> > WindowListenerList;
	WindowListenerList mWindowListeners;
};

#endif