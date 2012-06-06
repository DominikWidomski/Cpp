#include "GameUtil.h"
#include "GUIComponent.h"
#include "GameDisplay.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Default constructor. */
GameDisplay::GameDisplay(void) : mWidth(200), mHeight(200)
{
}

/** Construct display with given size. */
GameDisplay::GameDisplay(int w, int h) : mWidth(w), mHeight(h)
{
}

/** Destructor. */
GameDisplay::~GameDisplay(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Render display by rendering top level container. */
void GameDisplay::Render(void)
{
	// Update the projection matrix
	glMatrixMode(GL_PROJECTION);
	// Initialize the projection matrix to the identity matrix
	glLoadIdentity();
	// Set orthographic projection to include the world
	glOrtho(0, mWidth, 0, mHeight, -100, 100);
	// Switch to model mode ready for rendering
	glMatrixMode(GL_MODELVIEW);
	// Initialize the projection matrix to the identity matrix
	glLoadIdentity();

	mContainer.Draw();
}
