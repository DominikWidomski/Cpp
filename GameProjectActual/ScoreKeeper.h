#ifndef __SCOREKEEPER_H__
#define __SCOREKEEPER_H__

#include "GameUtil.h"

#include "GameObject.h"
#include "GameObjectType.h"
#include "IScoreListener.h"
#include "IGameWorldListener.h"
#include "Ore.h"

class ScoreKeeper : public IGameWorldListener
{
public:
	ScoreKeeper() { mScore = 0; }
	virtual ~ScoreKeeper() {}

	void OnWorldUpdated(GameWorld* world) {}

	void OnObjectAdded(GameWorld* world, SmartPtr<GameObject> object) {}

	void OnObjectRemoved(GameWorld* world, SmartPtr<GameObject> object)
	{
//		if (object->GetType() == GameObjectType("Asteroid")) {
//			mScore += 10;
//			FireScoreChanged();
//		}
		if (object->GetType() == GameObjectType("Ore")) {
            Ore* ore = (Ore*) object.GetPtr();
            mScore += ore->GetValue();
            FireScoreChanged();
		}
	}

	void AddListener(SmartPtr<IScoreListener> listener)
	{
		mListeners.push_back(listener);
	}

	void FireScoreChanged()
	{
		// Send message to all listeners
		for (ScoreListenerList::iterator lit = mListeners.begin(); lit != mListeners.end(); ++lit) {
			(*lit)->OnScoreChanged(mScore);
		}
	}

private:
	int mScore;

	typedef std::list< SmartPtr<IScoreListener> > ScoreListenerList;

	ScoreListenerList mListeners;
};

#endif
