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

#include <algorithm>
#include <cmath>

#include <OpenGL/gl.h>

#include "TiledKnot.h"

#include "KnotSection.h"
#include "Position.h"
#include "RandomNumbers.h"

namespace
{
    int kMaxSections = 6;
}

TiledKnot::TiledKnot(int windowWidth, int windowHeight, Position tilingDirection)
:   inherited(windowWidth, windowHeight,
              kMaxSections,
              tilingDirection.x ? 4 + randomInteger(4) : 1,
              tilingDirection.y ? 4 + randomInteger(4) : 1),
    mTilingDirection(tilingDirection)
{
    // empty
}

TiledKnot::~TiledKnot(void)
{
    // empty
}

// Find the intersection of the line (p0 + t*d) with the line through pe
// with normal n.  If no such intersection exists, return 'false';
// otherwise set t to the parameter value at the intersection point
// and return 'true'.
bool
TiledKnot::clipLine(Position p0, Position d, Position pe, Position n, GLfloat &t) const
{
    const GLfloat dot = n * d;
    if (fabs(dot) < 0.00001) {
        // Near parallel lines.
        return false;
    }

    // See Foley et.al.
    t = (n * (p0 - pe)) / -dot;
    return true;
}

// Find two values of the parameter t bounding the visible part of the line
// (p0 + t*d).  (We don't care about the case that the line is completely
// invisible.)
void
TiledKnot::findBounds(Position p0, Position d, GLfloat t[2]) const
{
    const GLfloat diag = norm(Size());
    bool clipH, clipV;
    GLfloat tt[4];

    // Clip against lower and upper borders of window.
    clipH = clipLine(p0, d,
                     Position(-mWindowWidth, -diag), Position(0.0, -1.0),
                     tt[0])
        &&  clipLine(p0, d,
                     Position(-mWindowWidth, mWindowHeight+diag), Position(0.0, 1.0),
                     tt[1]);

    // Clip against left and right borders of window.
    clipV = clipLine(p0, d,
                     Position(-diag, -mWindowHeight), Position(-1.0, 0.0),
                     tt[2])
        &&  clipLine(p0, d,
                     Position(mWindowWidth+diag, -mWindowHeight), Position(1.0, 0.0),
                     tt[3]);

    // Sort the intersections.
    ::std::sort(clipH ? (tt + 0) : (tt + 2), clipV ? (tt + 4) : (tt + 2));

    if (clipH && clipV) {
        // Find two intersections on opposite sides of the window.
        const Position midPosition(mWindowWidth * 0.5, mWindowHeight * 0.5);
        const GLfloat tm = (midPosition - p0) * d;

        const GLfloat *const p = ::std::lower_bound(tt + 0, tt + 4, tm);

        if (p > tt + 0 && p < tt + 4) {
            t[0] = p[-1];
            t[1] = p[0];
        } else {
            // This shouldn't hapen, but...
            t[0] = t[1] = 0;
        }
    } else if (!clipH) {
        t[0] = tt[2];
        t[1] = tt[3];
    } else {
        t[0] = tt[0];
        t[1] = tt[1];
    }
}

void
TiledKnot::draw(Position where, GLfloat angle) const
{
    const Position size(Size());
    const GLfloat step = size * mTilingDirection;

    const GLfloat rot[4] = { mTilingDirection.x, -mTilingDirection.y,
                             mTilingDirection.y,  mTilingDirection.x };
    const Position d = rot * Position(cos(angle), sin(angle));

    // Find the limits of visibility.
    GLfloat t[2];
    findBounds(where, d, t);
    const int minI = (int)floor(t[0] / step);
    const int maxI = (int)ceil(t[1] / step);

    // Draw the knot.
    for (int i = minI; i <= maxI; ++i) {
        const Position pos = where + i * step * d;

        glPushMatrix();
        {
            glTranslatef(pos.x, pos.y, 0.0);
            glRotatef(angle * 180.0 / M_PI, 0.0, 0.0, 1.0);
            glCallList(displayList());
        }
        glPopMatrix();
    }
}
