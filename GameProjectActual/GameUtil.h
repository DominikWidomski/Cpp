#ifndef __GAMEUTIL_H__
#define __GAMEUTIL_H__

#include <math.h>
#include <map>
#include <list>
#include <utility>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "SmartPtr.h"
#include "GLVector.h"
#include <GL/glut.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef unsigned char uchar;

using namespace std;
using namespace idllib;

template <typename VT>
float VectorMag(const VT &v)
{
    float mag = float(sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
    return mag;
}

// If M_PI has not been defined in math.h add it now
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define value to convert angles in degrees to radians
#define DEG2RAD (M_PI/180)
// Define value to convert radians to angles in degrees
#define RAD2DEG (180/M_PI)

#endif
