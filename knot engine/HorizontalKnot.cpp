//  A class representing a random horizontally tileable knot.
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

#include "HorizontalKnot.h"

#include "KnotSection.h"
class KnotStyle;
#include "Position.h"
#include "TiledKnot.h"
#include "RandomNumbers.h"

HorizontalKnot::HorizontalKnot(const KnotStyle &knotStyle,
                               int width, int height)
:   inherited(knotStyle, width, height, Position(1.0, 0.0))
{
    // Set boundary conditions for a horizontal knot.

    // The left and right borders must match.
    for (int i = 1; i < mVSections; ++i) {
        sectionCorner(mHSections, i) = sectionCorner(0, i);
    }

    // The top and bottom borders must have horizontal corners.
    for (int i = 0; i <= mHSections; ++i) {
        sectionCorner(i, 0) = sectionCorner(i, mVSections) = H;
    }

    // Assign colors to the knot.
    assignColors();
}

HorizontalKnot::~HorizontalKnot(void)
{
    // empty
}
