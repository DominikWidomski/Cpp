#include <GL/glut.h>
#include "IKeyboardListener.h"
#include "IMouseListener.h"
#include "IWindowListener.h"
#include "GlutSession.h"
#include "GlutWindow.h"

GlutWindow::GlutWindow(int w, int h, int x, int y, char* title)
{
	// Initialize values for window
	mWidth  = w;
	mHeight = h;
	mXCoord = x;
	mYCoord = y;
	mFullscreen = false;

	// Set initial display mode to use 32-bit colour and double buffering
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Set initial window size
	glutInitWindowSize(mWidth, mHeight);

	// Set initial window position
	glutInitWindowPosition(mXCoord, mYCoord);

	// Create the actual window with the given title
	mWindowID = glutCreateWindow(title);
}

GlutWindow::~GlutWindow(void)
{
}

void GlutWindow::OnDisplay(void)
{
	// Clear display
	glClear(GL_COLOR_BUFFER_BIT);
}

void GlutWindow::OnIdle(void)
{
}

void GlutWindow::OnTimer(int value)
{
}

void GlutWindow::OnKeyPressed(uchar key, int x, int y)
{
	// If the Esc key (code 27) has been pressed stop this session (exit program)
	if (key == 27) { GlutSession::Stop(); }

	// Send keyboard message to all listeners
	for (KeyboardListenerList::iterator it = mKeyboardListeners.begin(); it != mKeyboardListeners.end(); ++it) {
		(*it)->OnKeyPressed(key, x, y);
	}
}

void GlutWindow::OnKeyReleased(uchar key, int x, int y)
{
	// Send keyboard message to all listeners
	for (KeyboardListenerList::iterator it = mKeyboardListeners.begin(); it != mKeyboardListeners.end(); ++it) {
		(*it)->OnKeyReleased(key, x, y);
	}
}

void GlutWindow::OnSpecialKeyPressed(int key, int x, int y)
{
	// If the F1 key has been pressed, toggle the fullscreen window mode
	if (key == GLUT_KEY_F1) { SetFullscreen(!mFullscreen); }

	// Send keyboard message to all listeners
	for (KeyboardListenerList::iterator it = mKeyboardListeners.begin(); it != mKeyboardListeners.end(); ++it) {
		(*it)->OnSpecialKeyPressed(key, x, y);
	}
}

void GlutWindow::OnSpecialKeyReleased(int key, int x, int y)
{
	// Send keyboard message to all listeners
	for (KeyboardListenerList::iterator it = mKeyboardListeners.begin(); it != mKeyboardListeners.end(); ++it) {
		(*it)->OnSpecialKeyReleased(key, x, y);
	}
}

void GlutWindow::OnMouseDragged(int x, int y)
{
	// Send mouse message to all listeners
	for (MouseListenerList::iterator it = mMouseListeners.begin(); it != mMouseListeners.end(); ++it) {
		(*it)->OnMouseDragged(x, y);
	}
}

void GlutWindow::OnMouseButton(int button, int state, int x, int y)
{
	// Send mouse message to all listeners
	for (MouseListenerList::iterator it = mMouseListeners.begin(); it != mMouseListeners.end(); ++it) {
		(*it)->OnMouseButton(button, state, x, y);
	}
}

void GlutWindow::OnMouseMoved(int x, int y)
{
	// Send mouse message to all listeners
	for (MouseListenerList::iterator it = mMouseListeners.begin(); it != mMouseListeners.end(); ++it) {
		(*it)->OnMouseMoved(x, y);
	}
}

void  GlutWindow::OnWindowReshaped(int w, int h)
{
	// Send window message to all listeners
	for (WindowListenerList::iterator it = mWindowListeners.begin(); it != mWindowListeners.end(); ++it) {
		(*it)->OnWindowReshaped(w, h);
	}
}

void GlutWindow::OnWindowVisible(int visible)
{
	// Send window message to all listeners
	for (WindowListenerList::iterator it = mWindowListeners.begin(); it != mWindowListeners.end(); ++it) {
		(*it)->OnWindowVisible(visible);
	}
}

int GlutWindow::GetWindowID(void)
{
   return mWindowID;
}

void GlutWindow::SetFullscreen(bool fs)
{
	if (fs == mFullscreen) return;					// Return if no change required

	mFullscreen = fs;								// Set new window mode
	if (mFullscreen) {								// If change to fullscreen required
		mWidth = glutGet(GLUT_WINDOW_WIDTH);		// Save current window width
		mHeight = glutGet(GLUT_WINDOW_HEIGHT);		// Save current window height
		mXCoord = glutGet(GLUT_WINDOW_X);			// Save current window x-coord
		mYCoord = glutGet(GLUT_WINDOW_Y);			// Save current window y-coord
		glutFullScreen();							// Switch to fullscreen mode
	} else {										// If change to windowed required
		glutReshapeWindow(mWidth, mHeight);			// Restore window size
		glutPositionWindow(mXCoord, mYCoord);			// Restore window position
	}
}

void SetTimer(uint msecs, int value)
{
	GlutSession::RegisterWindowTimer(msecs, value);
}
