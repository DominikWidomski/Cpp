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

#include "GLVector.h"
    
template <>
void GLVector2<GLbyte>::glScale() const
{
    ::glScalef(val[0],val[1],0);
}

template <>
void GLVector2<GLshort>::glScale() const
{
    ::glScalef(val[0],val[1],0);
}

template <>
void GLVector2<GLint>::glScale() const
{
    ::glScalef(val[0],val[1],0);
}

template <>
void GLVector2<GLfloat>::glScale() const
{
    ::glScalef(val[0],val[1],0);
}

template <>
void GLVector2<GLdouble>::glScale() const
{
    ::glScaled(val[0],val[1],0);
}

template <>
void GLVector2<GLfloat>::glRotate(GLfloat ang) const
{
    ::glRotatef(ang,val[0],val[1],0);
}

template <>
void GLVector2<GLdouble>::glRotate(GLdouble ang) const
{
    ::glRotated(ang,val[0],val[1],0);
}

template <>
void GLVector2<GLfloat>::glTranslate() const
{
    ::glTranslatef(val[0],val[1],0);
}

template <>
void GLVector2<GLdouble>::glTranslate() const
{
    ::glTranslated(val[0],val[1],0);
}

template <>
void GLVector2<GLfloat>::glVertex() const
{
    ::glVertex2fv(val);
}

template <>
void GLVector2<GLdouble>::glVertex() const
{
    ::glVertex2dv(val);
}

template <>
void GLVector2<GLfloat>::glNormal() const
{
    ::glNormal3f(val[0],val[1],0);
}

template <>
void GLVector2<GLdouble>::glNormal() const
{
    ::glNormal3d(val[0],val[1],0);
}

template <>
void GLVector3<GLfloat>::glScale() const
{
    ::glScalef(val[0],val[1],val[2]);
}

template <>
void GLVector3<GLdouble>::glScale() const
{
    ::glScaled(val[0],val[1],val[2]);
}

template <>
void GLVector3<GLfloat>::glRotate(GLfloat ang) const
{
    ::glRotatef(ang,val[0],val[1],val[2]);
}

template <>
void GLVector3<GLdouble>::glRotate(GLdouble ang) const
{
    ::glRotated(ang,val[0],val[1],val[2]);
}

template <>
void GLVector3<GLfloat>::glTranslate() const
{
    ::glTranslatef(val[0],val[1],val[2]);
}

template <>
void GLVector3<GLdouble>::glTranslate() const
{
    ::glTranslated(val[0],val[1],val[2]);
}

template <>
void GLVector3<GLfloat>::glVertex() const
{
    ::glVertex3fv(val);
}

template <>
void GLVector3<GLdouble>::glVertex() const
{
    ::glVertex3dv(val);
}

template <>
void GLVector3<GLfloat>::glNormal() const
{
    ::glNormal3fv(val);
}

template <>
void GLVector3<GLdouble>::glNormal() const
{
    ::glNormal3dv(val);
}

template <>
void GLVector4<GLfloat>::glScale() const
{
    ::glScalef(val[0],val[1],val[2]);
}

template <>
void GLVector4<GLdouble>::glScale() const
{
    ::glScaled(val[0],val[1],val[2]);
}

template <>
void GLVector4<GLfloat>::glRotate(GLfloat ang) const
{
    ::glRotatef(ang,val[0],val[1],val[2]);
}

template <>
void GLVector4<GLdouble>::glRotate(GLdouble ang) const
{
    ::glRotated(ang,val[0],val[1],val[2]);
}

template <>
void GLVector4<GLfloat>::glTranslate() const
{
    ::glTranslatef(val[0],val[1],val[2]);
}

template <>
void GLVector4<GLdouble>::glTranslate() const
{
    ::glTranslated(val[0],val[1],val[2]);
}

template <>
void GLVector4<GLfloat>::glVertex() const
{
    ::glVertex4fv(val);
}

template <>
void GLVector4<GLdouble>::glVertex() const
{
    ::glVertex4dv(val);
}

template <>
void GLVector4<GLfloat>::glNormal() const
{
    ::glNormal3fv(val);
}

template <>
void GLVector4<GLdouble>::glNormal() const
{
    ::glNormal3dv(val);
}
