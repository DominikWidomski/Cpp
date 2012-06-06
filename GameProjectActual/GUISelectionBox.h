#ifndef __GUISELECTION_BOX__
#define __GUISELECTION_BOX__

#include "GUIComponent.h"

class GameObject;

class GUISelectionBox : public GUIComponent
{
public:
    GUISelectionBox();
    ~GUISelectionBox();

    void SetStart(GLVector2i s) { mStart = s; cout << "start:" << mStart << endl; }
    void SetMouse(GLVector2i m) {   mMouse = m;
                                    //cout << "mouse:" << mMouse << endl;
                                }

    void SetWorldCoord1(GLVector3f w1) { mWorldCoord1 = w1; }
    void SetWorldCoord2(GLVector3f w2) { mWorldCoord2 = w2; }

    //0verride of a virtual GUIComponent function
    virtual void Draw();

    bool CheckUnitWithin(SmartPtr<GameObject> object);
    void Reset() { mStart = GLVector2i(0,0); mMouse = GLVector2i(0,0); }
    void GiveDisplayDimensions(int w, int h) { mDisplayWidth = w; mDisplayHeight = h; }

protected:
    GLVector2i mStart;
    GLVector2i mMouse;

    GLVector3f mWorldCoord1;
    GLVector3f mWorldCoord2;

    int mDisplayWidth;
    int mDisplayHeight;
};

#endif

