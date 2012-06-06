#include "GUIComponent.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** default constructor. */
GUIComponent::GUIComponent()
	: mPosition(0, 0),
	  mBorder(0, 0),
	  mHorizontalAlignment(GUI_HALIGN_LEFT),
	  mVerticalAlignment(GUI_VALIGN_BOTTOM),
	  mColor(1, 1, 1),
	  mVisible(true)
{
}

/** Destructor. */
GUIComponent::~GUIComponent()
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Draw this component. */
void GUIComponent::Draw()
{
}
