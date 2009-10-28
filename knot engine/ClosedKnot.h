//  A class representing a random closed knot.
//
//  Copyright © 1997-2009  Jens Kilian
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

#ifndef CLOSEDKNOT_H
#define CLOSEDKNOT_H

#include <OpenGL/gl.h>

class KnotStyle;
#include "Position.h"
#include "RectangularKnot.h"

class ClosedKnot : public RectangularKnot
{
    typedef RectangularKnot inherited;
public:
    ClosedKnot(const KnotStyle &knotStyle,
               int windowWidth, int windowHeight);
    virtual ~ClosedKnot(void);

private:
    ClosedKnot(const ClosedKnot &orig);
    ClosedKnot &operator =(ClosedKnot &orig);

    virtual void
    draw(Position where, GLfloat angle) const;
};

#endif // CLOSEDKNOT_H
