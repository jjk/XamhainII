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

#include "CircularKnot.h"

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

CircularKnot::CircularKnot(int windowWidth, int windowHeight)
:   inherited(windowWidth, windowHeight, 6),
    mSectors(3 + randomInteger(5))
{
    // Set boundary conditions.

    // The left and right borders must have vertical corners.
    for (int i = 0; i <= mVSections; ++i) {
        sectionCorner(0, i) = sectionCorner(mHSections, i) = V;
    }

    // The top and bottom borders must match.
    for (int i = 1; i < mHSections; ++i) {
        sectionCorner(i, mVSections) = sectionCorner(i, 0);
    }

    // Calculate dimensions of the knot.
    const GLfloat fraction = randomFloat(mPrefs.minSize(), mPrefs.maxSize());

    const GLfloat outRadius =
        0.5 * fraction * ::std::min(mWindowWidth, mWindowHeight);
    const GLfloat inRadius =
        outRadius * randomFloat(0.25, 0.75);
    const GLfloat midRadius =
        (outRadius + inRadius) * 0.5;
    const int sectionWidth =
        (int)((outRadius - inRadius) / mHSections);

    const GLfloat angle = 2.0 * M_PI / mSectors;
    const int sectionHeight =
        (int)(angle * midRadius / mVSections);

    mEdgeLength =
        ::std::max(::std::max(sectionWidth, sectionHeight),
                   (mHollow ? 3 : 1) * kMinEdgeLength);
    mRadius =
        ::std::max(mVSections / angle, (mHSections+1) * 0.5f) * mEdgeLength;

    // Avoid infelicitous associations.
    if (mSectors == 4) {
        enforceVerticalSymmetry(false);
    }

    // Calculate the remaining properties.
    prepareAnimation(
        Position(1.0, 1.0) * (mRadius + mHSections * mEdgeLength * 0.5));
    assignColors();
}

CircularKnot::~CircularKnot(void)
{
    // empty
}

void
CircularKnot::drawBasicKnot(void) const
{
    const GLfloat angle = 2.0 * M_PI / mSectors / mVSections;
    const GLfloat minRadius = mRadius - mEdgeLength * 0.5 * (mHSections-1);

    // Draw all the sections.
    for (int i = 0; i < mVSections; ++i) {
        const GLfloat phi = (0.5 * (mVSections-1) - i) * angle;

        for (int j = 0; j < mHSections; ++j) {
            const GLfloat radius = minRadius + j * mEdgeLength;

            glPushMatrix();
            {
                glRotatef(phi * 180.0 / M_PI, 0.0, 0.0, 1.0);
                glTranslatef(radius, 0.0, 0.0);

                KnotSection section(sectionType(j, i),
                                    sectionCorner(j,   i),
                                    sectionCorner(j+1, i),
                                    sectionCorner(j,   i+1),
                                    sectionCorner(j+1, i+1));
                const GLfloat *pTopColor = sectionColor(TOP, j, i);
                const GLfloat *pBotColor = sectionColor(BOT, j, i);
                const GLfloat *pLTColor  = leftTopCornerColor(j, i);
                const GLfloat *pRBColor  = rightBottomCornerColor(j, i);

                section.draw(Position(0.0, 0.0), mEdgeLength, radius, angle,
                             *mpOutlineStrokes, *mpFillStrokes, mHollow,
                             pTopColor, pBotColor, pLTColor, pRBColor);
            }
            glPopMatrix();
        }
    }
}

void
CircularKnot::draw(Position where, GLfloat angle) const
{
    glPushMatrix();
    {
        glTranslatef(where.x, where.y, 0.0);
        glRotatef(angle * 180.0 / M_PI, 0.0, 0.0, 1.0);

        for (int i = 0; i < mSectors; ++i) {
            glCallList(displayList());
            glRotatef(360.0 / mSectors, 0.0, 0.0, 1.0);
        }
    }
    glPopMatrix();
}
