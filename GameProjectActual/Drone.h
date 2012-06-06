#ifndef __DRONE_H__
#define __DRONE_H__

#include "GameUtil.h"
#include "GameSession.h"
#include "Shape.h"
#include "GameObject.h"
#include "Order.h"

class Drone : public GameObject
{
public:
    Drone();
    Drone(int _x, int _y);
    ~Drone(void);

    bool CollisionTest(SmartPtr<GameObject> o);
    void OnCollision(const GameObjectList& objects);

    bool SelectionTest(GLVector3f w);

    void Update(int t);
    void Render();

    void ShootAtTarget(SmartPtr<GameObject> t);
    void DealDamage(int d) { mHealth -= d; }

    void AssignOrder(SmartPtr<Order> o) { mOrder = o; }
    void RemoveOrder() { mOrder = NULL; }

    void SetBulletShape(SmartPtr<Shape> bullet_shape) { mBulletShape = bullet_shape; }

//    void SetDroneShape(SmartPtr<Shape> drone_shape) { mDroneShape = drone_shape; }

protected:
//    SmartPtr<Shape> mDroneShape;

    SmartPtr<Order> mOrder;
    float mMaxSpeed;
    float mSpeed;
    int mFireTimer;
    int mFireReloadTime;
    int mHealth;

    SmartPtr<Shape> mBulletShape;
};

#endif

