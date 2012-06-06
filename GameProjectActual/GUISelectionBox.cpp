#include "GUISelectionBox.h"
#include "GameObject.h"

//GUISelectionBox::GUISelectionBox() : mStart(GLVector2f(0,0)), mMouse(GLVector2f(0,0))
//{}

/** Default constructor */
GUISelectionBox::GUISelectionBox() : mStart(GLVector2i(0,0)), mMouse(GLVector2i(0,0))
{
    SetVisible(false);
}

/** Destructor */
GUISelectionBox::~GUISelectionBox()
{
}

bool GUISelectionBox::CheckUnitWithin(SmartPtr<GameObject> unit) {

//    int zl = 2;
//    GLVector2i mCameraFocus(0,0);

    // Convert input mouse coordinates to world coordinates
//    GLVector3f world1((mStart.x - mDisplayWidth/2)/zl + mCameraFocus.x, (mDisplayHeight/2 - mStart.y)/zl + mCameraFocus.y, 0.0);
//    GLVector3f world2((mMouse.x - mDisplayWidth/2)/zl + mCameraFocus.x, (mDisplayHeight/2 - mMouse.y)/zl + mCameraFocus.y, 0.0);

    // Check where the boundaries of the box are
    int left, right, top, bottom;

    if(mWorldCoord1.x < mWorldCoord2.x) {
        left = mWorldCoord1.x; right = mWorldCoord2.x;
    } else {
        left = mWorldCoord2.x; right = mWorldCoord1.x;
    }

    if (mWorldCoord1.y < mWorldCoord2.y) {
        bottom = mWorldCoord1.y; top = mWorldCoord2.y;
    } else {
        bottom = mWorldCoord2.y; top = mWorldCoord1.y;
    }

    GLVector3f pos(unit->GetPosition());

//    cout << endl;
//    cout << "SELECTION BOX: [" << mStart << ",\t" << mMouse << "]" << endl;
//    cout << "SELECTION WRD: [" << world1 << ",\t" << world2 << "]" << endl;
//    cout << "LEFT    RIGHT: [" << left << ",\t" << right << "]" << endl;
//    cout << "TOP    BOTTOM: [" << top << ",\t" << bottom << "]" << endl;

    if(pos.x > left && pos.x < right && pos.y > bottom && pos.y < top) {
        return true;
    } else {
        return false;
    }
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////

/** Draw selection box by drawing a quad */
void GUISelectionBox::Draw()
{
    if(!mVisible) return;

    // Translate the Mouse input coordinates to the GUI drawing coordinates
    GLVector2i gui1(mStart.x, mDisplayHeight - mStart.y);
    GLVector2i gui2(mMouse.x, mDisplayHeight - mMouse.y);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_POLYGON_STIPPLE);

    // Draw the fill of the selection box using a quad
    glBegin(GL_QUADS);
        // Set colour
        glColor4f(1.0, 1.0, 1.0, 0.1);
        // Add vertices
        glVertex2i(gui1.x, gui1.y);
        glVertex2i(gui1.x, gui2.y);
        glVertex2i(gui2.x, gui2.y);
        glVertex2i(gui2.x, gui1.y);
        // Finish drawing the quad
    glEnd();

    // Draw the outline of the selection box using a line loop
    glBegin(GL_LINES);
        // Set colour
        glColor4f(1.0, 1.0, 1.0, 0.4);
        // Draw vertices
        glVertex2i(gui1.x, gui1.y);
        glVertex2i(gui1.x, gui2.y);
        glVertex2i(gui2.x, gui2.y);
        glVertex2i(gui2.x, gui1.y);
    glEnd();

//    glClear(GL_COLOR_BUFFER_BIT);

//    glDisable(GL_COLOR_MATERIAL);
//    glDisable(GL_BLEND);
}
