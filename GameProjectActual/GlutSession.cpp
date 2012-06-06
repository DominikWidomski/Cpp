#include <GL/glut.h>
#include <stdlib.h>
#include "ITimerListener.h"
#include "GlutWindow.h"
#include "GlutSession.h"

#include <limits.h>

GlutWindow* GlutSession::mWindow = NULL;
bool GlutSession::mIdleFunctionEnabled = false;

void GlutSession::CallBackDisplayFunc(void)
{
	// Pass callback to window
	if (mWindow) mWindow->OnDisplay();
}

void GlutSession::CallBackIdleFunc(void)
{
	// Pass callback to window
	if (mWindow && mIdleFunctionEnabled) { mWindow->OnIdle(); }
}

void GlutSession::CallBackKeyboardFunc(uchar key, int x, int y)
{
	// Pass callback to window
	if (mWindow) mWindow->OnKeyPressed(key, x, y);
}

void GlutSession::CallBackKeyboardUpFunc(uchar key, int x, int y)
{
	// Pass callback to window
	if (mWindow) mWindow->OnKeyReleased(key, x, y);
}

void GlutSession::CallBackSpecialFunc(int key, int x, int y)
{
	// Pass callback to window
	if (mWindow) mWindow->OnSpecialKeyPressed(key, x, y);
}

void GlutSession::CallBackSpecialUpFunc(int key, int x, int y)
{
	// Pass callback to window
	if (mWindow) mWindow->OnSpecialKeyReleased(key, x, y);
}

void GlutSession::CallBackMotionFunc(int x, int y)
{
	// Pass callback to window
	if (mWindow) mWindow->OnMouseDragged(x, y);
}

void GlutSession::CallBackMouseFunc(int button, int state, int x, int y)
{
	// Pass callback to window
	if (mWindow) mWindow->OnMouseButton(button, state, x, y);
}

void GlutSession::CallBackPassiveMotionFunc(int x, int y)
{
	// Pass callback to window
	if (mWindow) mWindow->OnMouseMoved(x, y);
}

void GlutSession::CallBackReshapeFunc(int w, int h)
{
	// Pass callback to window
	if (mWindow) mWindow->OnWindowReshaped(w, h);
}

void GlutSession::CallBackVisibilityFunc(int visibility)
{
	// Pass callback to window
	if (mWindow) mWindow->OnWindowVisible(visibility);
}

void GlutSession::CallBackSessionTimerFunc(int value)
{
	// Pass callback to window
	GlutSession::GetInstance().OnTimer(value);
}

void GlutSession::CallBackWindowTimerFunc(int value)
{
	// Pass callback to window
	if (mWindow) mWindow->OnTimer(value);
}

void GlutSession::RegisterCallbacks()
{
	// Register all callback functions
	glutDisplayFunc(CallBackDisplayFunc);
	glutKeyboardFunc(CallBackKeyboardFunc);
	glutSpecialFunc(CallBackSpecialFunc);
	glutSpecialUpFunc(CallBackSpecialUpFunc);
	glutMouseFunc(CallBackMouseFunc);
	glutMotionFunc(CallBackMotionFunc);
	glutPassiveMotionFunc(CallBackPassiveMotionFunc);
	glutReshapeFunc(CallBackReshapeFunc);
	glutVisibilityFunc(CallBackVisibilityFunc);

	// If window exists, initialize the idle loop
	if (mWindow) { glutIdleFunc(CallBackIdleFunc); } else { glutIdleFunc(0); }
}

void GlutSession::RegisterSessionTimer(uint msecs, int value)
{
	// Register callback function for session based timers
	glutTimerFunc(msecs, CallBackSessionTimerFunc, value);
}

void GlutSession::RegisterWindowTimer(uint msecs, int value)
{
	// Register callback function for window based timers
	glutTimerFunc(msecs, CallBackWindowTimerFunc, value);
}

void GlutSession::SetTimer(uint msecs, ITimerListener* listener, int value)
{
	// A unique key for timer event
	static int key = INT_MIN;
	if (++key == INT_MAX) key = INT_MIN;
	// Store listener and value
	mTimerListeners[key] = ListenerValuePair(listener, value);
	// Register timer event
	RegisterSessionTimer(msecs, key);
}

void GlutSession::OnTimer(int key)
{
	// Retrieve listener and value given key
	TimerListenerMap::iterator i = mTimerListeners.find(key);
	if (i == mTimerListeners.end()) return;
	ITimerListener* listener = (i->second).first;
	int value = (i->second).second;
	// Call listener with value
	listener->OnTimer(value);
	// Remove listener and value
	mTimerListeners.erase(i);
}

void GlutSession::Init(int &argc, char* argv[])
{
	// Initialize GLUT
	glutInit(&argc, argv);
}

void GlutSession::Start()
{
	// Enter main loop (this call will not return)
	glutMainLoop();
}

void GlutSession::Stop()
{
	// Exit program with no errors
	::exit(0);
}

GlutWindow* GlutSession::GetWindow(void)
{
	// Get the current window
	return mWindow;
}

void GlutSession::SetWindow(GlutWindow* w)
{
	// Set the current window
	mWindow = w;

	// Register call functions, must be done for every new window
	RegisterCallbacks();
}
