//  A class representing a random rectangular knot.
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

#ifndef RECTANGULARKNOT_H
#define RECTANGULARKNOT_H

#include <OpenGL/gl.h>

class KnotStyle;
#include "Position.h"
#include "RandomKnot.h"

class RectangularKnot : public RandomKnot
{
    typedef RandomKnot inherited;
public:
    RectangularKnot(const KnotStyle &knotStyle,
                    int windowWidth, int windowHeight,
                    int maxSections, int xRepeat = 1, int yRepeat = 1);
    virtual ~RectangularKnot(void);

protected:
    // Return the size of the basic knot.
    Position
    Size(void) const
    {
        return mEdgeLength * Position(mHSections, mVSections);
    }

    // Draw the basic knot at the origin.
    virtual void
    drawBasicKnot(void) const;

private:
    RectangularKnot(const RectangularKnot &orig);
    RectangularKnot &operator =(RectangularKnot &orig);

    // Data members.
    GLfloat mEdgeLength;
};

#endif // RECTANGULARKNOT_H
