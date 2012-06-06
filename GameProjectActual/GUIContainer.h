#ifndef __GUICONTAINER_H__
#define __GUICONTAINER_H__

#include "GameUtil.h"
#include "GUIComponent.h"

typedef map< SmartPtr<GUIComponent>, GLVector2f > GUIComponentMap;

class GUIContainer : public GUIComponent
{
public:
	GUIContainer();
	virtual ~GUIContainer();
	virtual void Draw();
	virtual void SetSize(const GLVector2i& size);
	void AddComponent( SmartPtr<GUIComponent> component, GLVector2f position );
	void RemoveComponent( SmartPtr<GUIComponent> component );
protected:
	void LayoutComponents();
	GUIComponentMap mComponents;
	bool mLayoutRequired;
};

#endif