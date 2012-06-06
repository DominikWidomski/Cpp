#ifndef __ORDER_H__
#define __ORDER_H__

#include "GameUtil.h"
#include "GameObject.h"

class GameObject;


    typedef enum { ORDER_MOVE, ORDER_ATTACK } OrderType_t;


class Order
{
public:
    Order(OrderType_t type);
    ~Order();

    void Update(int t, GameObject* go);

    void SetTarget(SmartPtr<GameObject> t) { mTarget = t; }
    void SetDestination(GLVector3f p) { mDestination = p; }

    OrderType_t GetType() { return mOrderType; }
    GLVector3f GetDestination() { return mDestination; }

    GLVector3f Steer(GLVector3f from, GLVector3f to);

    bool isComplete() { return mComplete; }

protected:
    OrderType_t mOrderType;
    SmartPtr<GameObject> mTarget;
    GLVector3f mDestination;

    bool mComplete;
};

#endif
