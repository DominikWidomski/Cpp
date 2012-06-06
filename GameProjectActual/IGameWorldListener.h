#ifndef __IGAMEWORLDLISTENER_H__
#define __IGAMEWORLDLISTENER_H__

#include "GameUtil.h"

class GameWorld;
class GameObject;

class IGameWorldListener
{
public:
	virtual void OnWorldUpdated(GameWorld* world) = 0;
	virtual void OnObjectAdded(GameWorld* world, SmartPtr<GameObject> object) = 0;
	virtual void OnObjectRemoved(GameWorld* world, SmartPtr<GameObject> object) = 0;
};

#endif