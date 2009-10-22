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

#include "ClosedKnot.h"

#include <cmath>

#include <OpenGL/gl.h>

#include "KnotSection.h"
#include "Position.h"

ClosedKnot::ClosedKnot(int windowWidth, int windowHeight)
:   inherited(windowWidth, windowHeight, 12)
{
    // Set boundary conditions for a closed knot.

    // The left and right border must consist of vertical...
    for (int i = 0; i < mVSections; ++i) {
        sectionType(0, i) = sectionType(mHSections-1, i) = V;
    }

    // ... half sections.
    for (int i = 0; i <= mVSections; ++i) {
        sectionCorner(0, i) = sectionCorner(mHSections, i) = N;
    }

    // The top and bottom border must have horizontal corners.
    for (int i = 1; i < mHSections; ++i) {
        sectionCorner(i, 0) = sectionCorner(i, mVSections) = H;
    }

    // Assign colors to the knot.
    assignColors();
}

ClosedKnot::~ClosedKnot(void)
{
    // empty
}

void
ClosedKnot::draw(Position where, GLfloat angle) const
{
    glPushMatrix();
    {
        glTranslatef(where.x, where.y, 0.0);
        glRotatef(angle * 180.0 / M_PI, 0.0, 0.0, 1.0);
        glCallList(displayList());
    }
    glPopMatrix();
}
