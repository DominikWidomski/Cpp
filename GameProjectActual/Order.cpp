#include <stdlib.h>
#include "Order.h"
#include "Drone.h"

Order::Order(OrderType_t type) : mOrderType(type), mComplete(false)
{
    cout << "Created a new Order of type: " << type << endl;
}

Order::~Order()
{
}

/** @brief Update
  *
  * @todo: document this function
  */
void Order::Update(int t, GameObject* go)
{
    float dt = t / 1000.0;

//    go->AddAcceleration();

    if(mOrderType == ORDER_MOVE)
    {
        float diffx = mDestination.x - go->GetPosition().x;
        float diffy = mDestination.y - go->GetPosition().y;

        if((mDestination - go->GetPosition()).length() > 10)
        {

            // steering vector
            GLVector3f steer(0.0, 0.0, 0.0);
            // vector pointing from the location to the target
            GLVector3f desired(mDestination.x - go->GetPosition().x, mDestination.y - go->GetPosition().y, 0.0);
            float mag = desired.length();

            if(mag > 0)
            {
                // normalize the desired vector
                desired.normalize();
                desired *= 10;
            }

            steer = (desired - go->GetVelocity());

            GLVector3f newAcceleration = GLVector3f(go->GetAcceleration().x + steer.x, go->GetAcceleration().y + steer.y, 0.0);
            go->SetAcceleration(newAcceleration);

            float newAng = (float) atan2(diffy,diffx);
//        go->SetAngle(RAD2DEG*newAng);
            go->SetAngle(RAD2DEG*newAng);
//        cout << "ANGLE: " << go->GetAngle() << endl;
//
        //go->SetAcceleration(GLVector3f(cos(newAng), sin(newAng), 0.0));

        go->AddVelocity(go->GetAcceleration());

        go->AddPosition(go->GetVelocity() * dt);

        }
        else
        {
            go->SetAcceleration(GLVector3f(0.0, 0.0, 0.0));
            go->SetVelocity(GLVector3f(0.0, 0.0, 0.0));
        }
    }

    if( mOrderType == ORDER_ATTACK)
    {
        Drone* d = (Drone*) go;

        float diffx = mTarget->GetPosition().x - go->GetPosition().x;
        float diffy = mTarget->GetPosition().y - go->GetPosition().y;

        float newAng = (float) atan2(diffy, diffx);

        go->SetAngle(RAD2DEG*newAng);

        cout << "Going to fire nao\n";
        d->ShootAtTarget(mTarget);
    }
}

GLVector3f Order::Steer(GLVector3f from, GLVector3f to)
{
    // steering vector
    GLVector3f steer(0.0, 0.0, 0.0);
    // vector pointing from the location to the target
    GLVector3f desired(to.x - from.x, to.y - from.y, 0.0);
    float mag = desired.length();

    if(mag > 0)
    {
        // normalize the desired vector
        desired.normalize();
        desired *= 10;
    }

//    steer = (desired - go->GetVelocity());

    float diffx = to.x - from.x;
    float diffy = to.y - from.y;

    float distance = (from - to).length();

    return steer;
}
