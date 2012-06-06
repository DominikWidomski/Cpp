#ifndef __UNITMANAGER_H__
#define __UNITMANAGER_H__

//#include "Drone.h"
#include "GameUtil.h"
#include <vector>

class GameObject;

class UnitManager
{
    typedef std::vector< SmartPtr< GameObject > > GameObjectVector;

public:
    UnitManager();
    virtual ~UnitManager();

    void UpdateAll();
    void RenderAll();

    void AddUnitTeam1(SmartPtr<GameObject> go) { mAllUnits.push_back(go); mTeam1.push_back(go); }
    void AddUnitTeam2(SmartPtr<GameObject> go) { mAllUnits.push_back(go); mTeam2.push_back(go); }

    GameObjectVector GetAllUnits()      { return mAllUnits; }
    GameObjectVector GetTeam1()         { return mTeam1; }
    GameObjectVector GetTeam2()         { return mTeam2; }
    GameObjectVector GetSelectedUnits() { return mSelectedUnits; }

protected:
    GameObjectVector mAllUnits;
    GameObjectVector mTeam1;
    GameObjectVector mTeam2;
    GameObjectVector mSelectedUnits;
};

#endif
