//  A class representing a random vertically tileable knot.
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

#include "VerticalKnot.h"

#include "KnotSection.h"
class KnotStyle;
#include "Position.h"
#include "TiledKnot.h"
#include "RandomNumbers.h"

VerticalKnot::VerticalKnot(const KnotStyle &knotStyle,
                           int width, int height)
:   inherited(knotStyle, width, height, Position(0.0, 1.0))
{
    // Set boundary conditions for a vertical knot.

    // The left and right borders must have vertical corners.
    for (int i = 0; i <= mVSections; ++i) {
        sectionCorner(0, i) = sectionCorner(mHSections, i) = V;
    }

    // The top and bottom borders must match.
    for (int i = 1; i < mHSections; ++i) {
        sectionCorner(i, mVSections) = sectionCorner(i, 0);
    }

    // Assign colors to the knot.
    assignColors();
}

VerticalKnot::~VerticalKnot(void)
{
    // empty
}
