//  A class representing a random circular knot.
//
//  Copyright © 2004-2009  Jens Kilian
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

#ifndef CIRCULARKNOT_H
#define CIRCULARKNOT_H

#include <OpenGL/gl.h>

class KnotStyle;
#include "Position.h"
#include "RandomKnot.h"

class CircularKnot : public RandomKnot
{
    typedef RandomKnot inherited;
public:
    CircularKnot(const KnotStyle &knotStyle,
                 int windowWidth, int windowHeight);
    virtual ~CircularKnot(void);

private:
    CircularKnot(const CircularKnot &orig);
    CircularKnot &operator =(CircularKnot &orig);

    // Draw the basic knot at the origin.
    virtual void
    drawBasicKnot(void) const;

    virtual void
    draw(Position where, GLfloat angle) const;

    // Data members.
    int mSectors;
    GLfloat mEdgeLength;
    GLfloat mRadius;
};

#endif // CIRCULARKNOT_H
