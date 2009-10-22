//  Description of knot strokes and sections.
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

//  Traditionally, Celtic knotwork is drawn on a diagonal grid
//  overlaid with straight lines and circles.  Xamhain uses
//  a simpler method devised by Andy Sloss, which divides the knot
//  into sections at every other grid point.  Each section can be
//  uniquely described by the directions in which the knot passes
//  through the section's corners, plus the directions the two lines
//  take in the interior of the section.
//  There are three possible directions (diagonal, horizontal and
//  vertical), so there are 3^5 = 243 basic sections.  The horizontal
//  and vertical sections can be split in half for closing up the edges
//  of a knot, yielding another 36 shapes.  These are represented
//  as a section with two corners that have "no" direction.
//
//  Because of symmetries, the 279 different sections can be drawn
//  using only 10 basic strokes - see class StrokeSet.

#ifndef KNOTSECTION_H
#define KNOTSECTION_H

#include <OpenGL/gl.h>

#include "Position.h"
class StrokeSet;

enum Direction {		// Directions of strokes and sections.
    D = 0,			// diagonal
    H = 1,			// horizontal
    V = 2,			// vertical
    N = 3                       // none (edge sections only)
};

// Identify the two 'strands' in a section.
enum { BOT, TOP };

class KnotSection {
    const Direction mType, mLT, mRT, mLB, mRB;

public:
    KnotSection(Direction tp,
                Direction lt, Direction rt, Direction lb, Direction rb)
    :    mType(tp), mLT(lt), mRT(rt), mLB(lb), mRB(rb)
    {
        // empty
    }

    Direction type(void) const        { return mType; }
    Direction leftTop(void) const     { return mLT; }
    Direction rightTop(void) const    { return mRT; }
    Direction leftBottom(void) const  { return mLB; }
    Direction rightBottom(void) const { return mRB; }

    // Draw the section at the given location and size, using the strokes
    // and colors to determine how it will look.  If radius and angle,
    // are non-zero, the stroke is warped into a segment of an annulus.
    void
    draw(Position center, GLfloat size, GLfloat radius, GLfloat angle,
         const StrokeSet &outlineStrokes, const StrokeSet &fillStrokes,
         bool hollow,
         const GLfloat topColor[4], const GLfloat botColor[4],
         const GLfloat ltCornerColor[4], const GLfloat rbCornerColor[4]) const;
};

#endif // KNOTSECTION_H
