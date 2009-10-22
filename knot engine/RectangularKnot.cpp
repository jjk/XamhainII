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

#include "RectangularKnot.h"

#include <cmath>
#include <algorithm>
#include <OpenGL/gl.h>

#include "KnotSection.h"
#include "Position.h"
#include "RandomKnot.h"
#include "RandomNumbers.h"

namespace
{
    // Minimum size of knot sections.
    const int kMinEdgeLength = 10;
}

RectangularKnot::RectangularKnot(int windowWidth, int windowHeight,
                                 int maxSections, int xRepeat, int yRepeat)
:   inherited(windowWidth, windowHeight, maxSections)
{
    // Calculate dimensions of the knot.
    const GLfloat fraction = randomFloat(mPrefs.minSize(), mPrefs.maxSize());
    const int sectionWidth =
        (int)(fraction * mWindowWidth / mHSections / xRepeat);
    const int sectionHeight =
        (int)(fraction * mWindowHeight / mVSections / yRepeat);
    mEdgeLength =
        ::std::max(::std::max(sectionWidth, sectionHeight),
                 (mHollow ? 3 : 1) * kMinEdgeLength);

    // Calculate the remaining properties.
    prepareAnimation(Position(mHSections, mVSections) * mEdgeLength * 0.5,
                     xRepeat > 1,
                     yRepeat > 1);
}

RectangularKnot::~RectangularKnot(void)
{
    // empty
}

void
RectangularKnot::drawBasicKnot(void) const
{
    const Position offset =
        - (mEdgeLength*0.5) * Position(mHSections-1, mVSections-1);

    // Draw all the sections.
    for (int i = 0; i < mVSections; ++i) {
        for (int j = 0; j < mHSections; ++j) {
            KnotSection section(sectionType(j, i),
                                sectionCorner(j,   i),
                                sectionCorner(j+1, i),
                                sectionCorner(j,   i+1),
                                sectionCorner(j+1, i+1));
            const GLfloat *pTopColor = sectionColor(TOP, j, i);
            const GLfloat *pBotColor = sectionColor(BOT, j, i);
            const GLfloat *pLTColor  = leftTopCornerColor(j, i);
            const GLfloat *pRBColor  = rightBottomCornerColor(j, i);

            section.draw(offset + mEdgeLength*Position(j, (mVSections-1 - i)),
                         mEdgeLength, 0.0, 0.0,
                         *mpOutlineStrokes, *mpFillStrokes, mHollow,
                         pTopColor, pBotColor, pLTColor, pRBColor);
        }
    }
}
