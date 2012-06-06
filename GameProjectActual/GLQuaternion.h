/***************************************************************************
 *   Copyright (C) 2004 by Jacques Gasselin                                *
 *   jacquesgasselin@hotmail.com                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef GLQUATERNION_H
#define GLQUATERNION_H

#include "GLVector.h"

/**
A quaternion is a 3D plane in imaginary space, or some say a 4D vector. It behaves mathematically much like a plane in 3D, where a rotation is a reflection about two planes, one with the normal at half the angle and another at the angle. It is useful for rotations in 3D space because multiplications of quaternions are commutative, ie. it doesn't matter in which order you do them.

@author Jacques Gasselin
*/
template <class T>
class GLQuaternion
{
public:
    /**Create a unit quaternion*/
    GLQuaternion()
    {    set(1,0,0,0); }

    /**Create a scaled directed quaternion*/
    GLQuaternion(T f, GLVector3<T> gv)
    {    set(f,gv); }

    /**Create a directed quaternion*/
    GLQuaternion(GLVector3<T> gv)
    {    set(0,gv); }

    /**Copy a quaternion*/
    GLQuaternion(const GLQuaternion& gq)
    {    set(gq.w, gq.v); }

    /**Create a rotation quaternion, *MOST PEOPLE WILL WANT TO USE THIS CONSTRUCTOR ONLY*
      *NB. Do not halve angle, this is done within the constructor.*/
    GLQuaternion(GLVector3<T> gv, T angle)
    {    set(gv.unit(), angle); }

    /**Default destructor*/
    ~GLQuaternion(){}

    /**Get real or plane constant*/
    inline T getW()
    {    return w; }

    /**Get imaginary or plane normal*/
    inline GLVector3<T> getV()
    {    return v; }

    /**Get imaginary or plane normal*/
    inline void set(T _w, GLVector3<T> gv)
    {    w = _w; v = gv; }

    /**Set from immediates*/
    inline void set(T _w, T x, T y, T z)
    {    w = _w; v.set(x,y,z); }

    /**Set from array, must be at least 4 elements long*/
    inline void set(const T* gq)
    {    set(gq[0],gq[1],gq[2],gq[3]); }

    /**Set from angle and normal, NB. Do not halve angle it is done internally*/
    inline void set(GLVector3<T> vec, T angle)
    {    set(cos(angle), vec * sin(angle/2) ); }

    /**Quaternion addition*/
    GLQuaternion operator + (GLQuaternion gq)
    {    GLQuaternion temp(*this); temp += gq; return temp; }

    /**Quaternion subtraction*/
    GLQuaternion operator - (GLQuaternion gq)
    {    GLQuaternion temp(*this); temp -= gq; return temp; }

    /**Quaternion self referenced addition*/
    GLQuaternion& operator += (GLQuaternion gq)
    {    w += gq.w; v += gq.v; return *this; }

    /**Quaternion self referenced subtraction*/
    GLQuaternion& operator -= (GLQuaternion gq)
    {    w -= gq.w; v -= gq.v; return *this; }

    /**Quaternion multiplication*/
    GLQuaternion operator * (GLQuaternion gq)
    {    GLQuaternion temp(*this); temp *=  gq; return temp; }

    /**Quaternion division, NB. Do not divide by 0, there are no safety catches for that*/
    GLQuaternion operator / (T f)
    {    GLQuaternion temp(*this); temp /= f; return temp; }

    /**Quaternion self referenced multiplication*/
    GLQuaternion& operator *= (GLQuaternion gq)
    {    set( w * gq.w - v.dot(gq.v) , (gq.v * w) + (v * gq.w) + v.getCross(gq.v) ); return *this; }

    /**Quaternion self referenced division*/
    GLQuaternion& operator /= (T f)
    {    set( w / f , v / f ); return *this; }

    /**Quaternion dot product*/
    T dot(GLQuaternion gq)
    {    return ( w*gq.w + v.dot(gq.v) ); }

    /**Quaternion cross product*/
    GLQuaternion getCross(GLQuaternion gq)
    {    return GLQuaternion( w * gq.w - v.dot(gq.v) , (gq.v * w) + (v * gq.w) + v.getCross(gq.v) ); }

    /**Quaternion complex conjugate*/
    GLQuaternion getConjugate()
    {    GLQuaternion temp(*this); temp.conjugate(); return temp; }

    /**Quaternion self referenced complex conjugate*/
    GLQuaternion& conjugate()
    {    v = -v; return *this; }

    /**Quaternion inverse (more like a normalised conjugate)*/
    GLQuaternion getInverse()
    {    GLQuaternion temp(*this); temp.inverse(); return temp; }

    /**Quaternion self referenced inverse (more like a normalised conjugate)*/
    GLQuaternion& inverse()
    {    conjugate(); *this /= norm(); return *this; }

    /**Real part*/
    T selection()
    {    return w; }

    /**Quaternion norm (similar to vector length)*/
    T norm()
    {    return sqrt( w*w + v.lengthSqr() ); }

    /**Quaternion self referenced normal*/
    GLQuaternion& unit()
    {    return (*this/=norm()); }

    /**GLVector interface method for ease of use. THIS IS PROBABLY THE ONLY METHOD YOU WOULD NORMALLY USE.
      *NB. Don't forget to normalise the quaternion unless you want axial translation as well as rotation*/
    GLVector3<T> rotateVector(GLVector3<T> gv)
    {    GLQuaternion temp = getCross(GLQuaternion(gv)); temp *= getConjugate(); return temp.v; }

private:
    /**The 3D imaginary vector*/
    GLVector3<T> v;
    /**The real plane constant*/
    T w;
};

/**OpenGL style interface, GLfloat*/
typedef GLQuaternion<GLfloat> GLQuaternionf;
/**OpenGL style interface, GLdouble*/
typedef GLQuaternion<GLdouble> GLQuaterniond;

#endif
