#include "GameUtil.h"
#include "GameWorld.h"
#include "IKeyboardListener.h"
#include "GameDisplay.h"
#include "GameWindow.h"

const int GameWindow::ZOOM_LEVEL = 2;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Construct a game window with given width, height, position and title. */
GameWindow::GameWindow(int w, int h, int x, int y, char *t)
	: GlutWindow(w, h, x, y, t),
	  mWorld(NULL),
	  mDisplay(NULL)
{
}

/**   Destructor. */
GameWindow::~GameWindow()
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Call world and display to render themselves. */
void GameWindow::OnDisplay(void)
{
	// Clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Render the world and display
	if (mWorld) { mWorld->Render(); }
	if (mDisplay) { mDisplay->Render(); }
	// Show the backbuffer
	glutSwapBuffers();
}

/** Update world and display. */
void GameWindow::OnIdle(void)
{
	// Call parent to do any idle loop processing
	GlutWindow::OnIdle();
	// Calculate the time in milliseconds since the last update
	static int lasttime;
	int dt=glutGet(GLUT_ELAPSED_TIME)-lasttime;
	lasttime=glutGet(GLUT_ELAPSED_TIME);
	// Update the world and display
	if (mWorld) { mWorld->Update(dt); }
	if (mDisplay) { mDisplay->Update(dt); }
	// Request a redisplay
	glutPostRedisplay();
}

/** Reshape viewport, world and display. */
void  GameWindow::OnWindowReshaped(int w, int h)
{
	// Call parent to handle default window reshaping
	GlutWindow::OnWindowReshaped(w, h);
	// Reshape the viewport to cover the whole window
	glViewport(0, 0, w, h);
	// Update the world and display to match
	UpdateWorldSize();
	UpdateDisplaySize();
}

void GameWindow::SetWorld(GameWorld* w) { mWorld = w; UpdateWorldSize(); }
GameWorld* GameWindow::GetWorld() { return mWorld; }

void GameWindow::SetDisplay(GameDisplay* d) { mDisplay = d; UpdateDisplaySize(); }
GameDisplay* GameWindow::GetDisplay() { return mDisplay; }

void GameWindow::UpdateWorldSize()
{
	// Set the width and height of the world based on zoom level
	if (mWorld) {
//		mWorld->SetWidth(glutGet(GLUT_WINDOW_WIDTH)/ZOOM_LEVEL);
//		mWorld->SetHeight(glutGet(GLUT_WINDOW_HEIGHT)/ZOOM_LEVEL);
        // TODO zoom?
        mWorld->SetWidth(glutGet(GLUT_WINDOW_WIDTH)/ZOOM_LEVEL);
		mWorld->SetHeight(glutGet(GLUT_WINDOW_HEIGHT)/ZOOM_LEVEL);

	}
}

void GameWindow::UpdateDisplaySize()
{
	// Set the width and height of the display
	if (mDisplay) {
		mDisplay->Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}
}
