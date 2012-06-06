#include "GUIContainer.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Default constructor */
GUIContainer::GUIContainer() : mLayoutRequired(false)
{
}

/** Destructor */
GUIContainer::~GUIContainer()
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Add a component to this container at the given relative position. */
void GUIContainer::AddComponent( SmartPtr<GUIComponent> component, GLVector2f position )
{
	mComponents[component] = position;
	mLayoutRequired = true;
}

/** Remove a component from this container. */
void GUIContainer::RemoveComponent( SmartPtr<GUIComponent> component )
{
	mComponents.erase( component );
}

/** Draw this container by drawing all of its components. */
void GUIContainer::Draw()
{
	if (mLayoutRequired) LayoutComponents();

	for (GUIComponentMap::iterator it = mComponents.begin(); it != mComponents.end(); ++it) {
		SmartPtr<GUIComponent> component = it->first;
		GLVector2f position = it->second;
		component->Draw();
	}
}

/** Set the size of this container. */
void GUIContainer::SetSize(const GLVector2i& size)
{
	GUIComponent::SetSize(size);
	LayoutComponents();
}

/** Layout all of this container's components using relative positions. */
void GUIContainer::LayoutComponents()
{
	for (GUIComponentMap::iterator it = mComponents.begin(); it != mComponents.end(); ++it) {
		SmartPtr<GUIComponent> ptr = it->first;
		GLVector2f position = it->second;
		int xpos = mPosition.x + mBorder.x + (int)((mSize.x - 2 * mBorder.x) * position.x);
		int ypos = mPosition.y + mBorder.y + (int)((mSize.y - 2 * mBorder.y) * position.y);
		ptr->SetPosition(GLVector2i(xpos, ypos));
	}
	mLayoutRequired = false;
}
