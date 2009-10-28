//  A class representing a random tiled knot.
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

#ifndef TILEDKNOT_H
#define TILEDKNOT_H

#include <OpenGL/gl.h>

class KnotStyle;
#include "Position.h"
#include "RectangularKnot.h"

class TiledKnot : public RectangularKnot
{
    typedef RectangularKnot inherited;
public:
    TiledKnot(const KnotStyle &knotStyle,
              int windowWidth, int windowHeight, Position tilingDirection);
    virtual ~TiledKnot(void);

private:
    TiledKnot(const TiledKnot &orig);
    TiledKnot &operator =(TiledKnot &orig);

    // Clip line (p0 + t*d) at a window boundary.
    bool
    clipLine(Position p0, Position d, Position pe, Position n, GLfloat &t) const;
    // Find two parameter values between which the knot will be visible.
    void
    findBounds(Position p0, Position d, GLfloat t[2]) const;

    // Draw the (replicated) knot.
    virtual void
    draw(Position where, GLfloat angle) const;

    // Data members.
    const Position mTilingDirection;
};

#endif // TILEDKNOT_H
