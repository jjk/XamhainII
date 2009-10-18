//  Arithmetic with coordinates.  BeOS rulez!
//
//  Copyright © 2001-2009  Jens Kilian
//
//  This file is part of XamhainII.
//
//  XamhainII is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  XamhainII is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with XamhainII.  If not, see <http://www.gnu.org/licenses/>.

#ifndef POINT_H
#define POINT_H

#include <cmath>

#include <OpenGL/gl.h>

class Point
{
public:
    GLfloat x;
    GLfloat y;

    Point(void)
    {
        // empty
    }

    Point(GLfloat x_, GLfloat y_)
    : x(x_), y(y_)
    {
        // empty
    }
};

// Just the operators we'll use; no need to provide the full set.
inline Point
operator +(const Point &p1, const Point &p2)
{
  return Point(p1.x + p2.x, p1.y + p2.y);
}

inline Point
operator -(const Point &p1, const Point &p2)
{
  return Point(p1.x - p2.x, p1.y - p2.y);
}

inline Point
operator *(const Point &p, const GLfloat s)
{
    return Point(p.x * s, p.y * s);
}

inline Point
operator *(const GLfloat s, const Point &p)
{
    return Point(p.x * s, p.y * s);
}

inline GLfloat
operator *(const Point &p1, const Point &p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}

inline Point
operator *(const GLfloat t[4], const Point &p)
{
    return Point(t[0] * p.x + t[1] * p.y,
                 t[2] * p.x + t[3] * p.y);
}

inline GLfloat
norm(const Point &p)
{
    return sqrt(p * p);
}

#endif // POINT_H
