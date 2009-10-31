//  Base class for creating random knots.
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

#include "RandomKnot.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <OpenGL/gl.h>

#include "KnotSection.h"
#include "KnotStyle.h"
#include "Position.h"
#include "RandomColor.h"
#include "RandomNumbers.h"
#include "StrokeSet.h"

namespace
{
    // Generate an array of random direction values.
    Direction *
    randomDirectionArray(int width, int height, GLfloat min, GLfloat max)
    {
        Direction *pArray = new Direction[width * height];
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                GLfloat p = randomFloat();
                if (p < min) {
                    pArray[i*width + j] = H;

                } else if (p < max) {
                    pArray[i*width + j] = D;

                } else {
                    pArray[i*width + j] = V;
                }
            }
        }

        return pArray;
    }

    // Enforce symmetry in an array of random direction values.
    void
    enforceSymmetry(Direction *pArray,
                    int width, int height,
                    int widthLimit, int heightLimit,
                    bool xMirror, bool yMirror)
    {
        for (int i0 = 0; i0 < heightLimit; ++i0) {
            const int i1 = yMirror ? height - i0 - 1 : i0;
            for (int j0 = 0; j0 < widthLimit; ++j0) {
                const int j1 = xMirror ? width - j0 - 1 : j0;

                pArray[i1*width + j1] = pArray[i0*width + j0];
            }
        }
    }
}

RandomKnot::RandomKnot(const KnotStyle &knotStyle,
                       int windowWidth, int windowHeight, int maxSections)
:   mWindowWidth(windowWidth),
    mWindowHeight(windowHeight),
    mHSections(3 + randomInteger(maxSections - 3)),
    mVSections(3 + randomInteger(maxSections - 3)),
    mOutlineStrokes(knotStyle.outline()),
    mFillStrokes(knotStyle.fill()),
    mHollow(randomFloat() < mPrefs.hollowKnotProbability()),
    mpSectionTypes(0),
    mpSectionCorners(0),
    mpColors(0),
    mDisplayList(0)
{
    // Initialize the knot data.  Derived classes have to establish
    // the proper boundary conditions.
    mpSectionTypes =
        randomDirectionArray(mHSections, mVSections,
                             mPrefs.sectionProbability1(),
                             mPrefs.sectionProbability2());
    mpSectionCorners =
        randomDirectionArray(mHSections + 1, mVSections + 1,
                             mPrefs.cornerProbability1(),
                             mPrefs.cornerProbability2());

    mpSectionColors[BOT] = new int[mHSections * mVSections];
    mpSectionColors[TOP] = new int[mHSections * mVSections];

    if (randomFloat() < mPrefs.symmetricKnotProbability()) {
        // Enforce symmetries.
        enforceHorizontalSymmetry(
            randomFloat() < mPrefs.horizontalMirrorProbability());
        enforceVerticalSymmetry(
            randomFloat() < mPrefs.verticalMirrorProbability());
    }
}

RandomKnot::~RandomKnot(void)
{
    delete [] mpSectionTypes;
    mpSectionTypes = 0;
    delete [] mpSectionCorners;
    mpSectionCorners = 0;
    delete [] mpSectionColors[BOT];
    mpSectionColors[BOT] = 0;
    delete [] mpSectionColors[TOP];
    mpSectionColors[TOP] = 0;
    delete [] mpColors;
    mpColors = 0;

    if (mDisplayList) {
        glDeleteLists(mDisplayList, 1);
        mDisplayList = 0;
    }
}

bool
RandomKnot::animate(void)
{
    if (mTime >= mMaxTime) {
        return false;
    }

    // Draw the knot in its current state.
    draw(mBasePosition + mTime * mDirection, mAngle);

    // Update the state.
    mTime += mSpeed;
    mAngle += mSpin;

    return true;
}

GLuint
RandomKnot::displayList(void) const
{
    if (!mDisplayList) {
        mDisplayList = glGenLists(1);

        // Generate the display list.
        glNewList(mDisplayList, GL_COMPILE);
        {
            drawBasicKnot();
        }
        glEndList();
    }

    return mDisplayList;
}

void
RandomKnot::enforceHorizontalSymmetry(bool mirror)
{
    enforceSymmetry(mpSectionTypes,
                    mHSections, mVSections,
                    mHSections / 2, mVSections,
                    true, mirror);
    enforceSymmetry(mpSectionCorners,
                    mHSections + 1, mVSections + 1,
                    (mHSections + 1) / 2, mVSections + 1,
                    true, mirror);
}

void
RandomKnot::enforceVerticalSymmetry(bool mirror)
{
    enforceSymmetry(mpSectionTypes,
                    mHSections, mVSections,
                    mHSections, mVSections / 2,
                    mirror, true);
    enforceSymmetry(mpSectionCorners,
                    mHSections + 1, mVSections + 1,
                    mHSections + 1, (mVSections + 1) / 2,
                    mirror, true);
}

void
RandomKnot::prepareAnimation(Position extent, bool xRepeat, bool yRepeat)
{
    // Find a random position within the window where the knot will be visible.
    const GLfloat knotWidth = 2.0 * extent.x;
    const GLfloat knotHeight = 2.0 * extent.y;
    if (knotWidth < mWindowWidth && knotHeight < mWindowHeight) {
        mBasePosition =
            Position(randomFloat(mWindowWidth - knotWidth),
                     randomFloat(mWindowHeight - knotHeight))
            + extent;
    } else {
        mBasePosition = Position(randomFloat() * mWindowWidth,
                                 randomFloat() * mWindowHeight);
    }

    // Give the knot a random speed, direction, angle and spin.
    mSpeed = randomFloat(mPrefs.minSpeed(), mPrefs.maxSpeed()) + 0.1;

    GLfloat dir;
    if (randomFloat() < mPrefs.skewProbability()) {
        dir = randomFloat(0.0, M_PI * 2.0);

        if (xRepeat) {
            mAngle = fmod(dir + M_PI_2, M_PI * 2.0);
        } else if (yRepeat) {
            mAngle = dir;
        } else {
            mAngle = randomFloat(0.0, M_PI * 2.0);
        }

    } else {
        int quad;
        if (xRepeat) {
            quad = 2 * randomInteger(2) + 1;
        } else if (yRepeat) {
            quad = 2 * randomInteger(2);
        } else {
            quad = randomInteger(4);
        }
        dir = quad * M_PI_2;
        mAngle = 0.0;
    }
    mDirection = Position(cos(dir), sin(dir));

    if (randomFloat() < mPrefs.spinProbability()) {
        mSpin = randomFloat(mPrefs.minSpin(), mPrefs.maxSpin())
            * ((randomFloat() < 0.5) ? 1.0 : -1.0)
            / 180.0 * M_PI;
    } else {
        mSpin = 0.0;
    }

    // Calculate the starting and stopping times, i.e., the time at which
    // the knot's bounding circle is tangent to the window's bounding circle.
    //
    // - project window midpoint to point P0 on line of movement at time T0.
    // - use Pythagoras to compute distance from P0 to center of knot
    // - calculate T0 - distance and T0 + distance
    const Position midPosition(mWindowWidth * 0.5, mWindowHeight * 0.5);
    const GLfloat t0 = (midPosition - mBasePosition) * mDirection;
    const Position p0 = mBasePosition + t0 * mDirection;

    const GLfloat hyp = norm(midPosition) + norm(extent);
    const GLfloat cat = norm(midPosition - p0);
    const GLfloat distance = sqrt(hyp * hyp - cat * cat);

    mTime    = t0 - distance;
    mMaxTime = t0 + distance;

    // Adjust the spin rate so the angle is consistent at start and stop.
    GLfloat iterations = floor((mMaxTime - mTime) / mSpeed);
    mSpin = floor(mSpin / M_PI * iterations) * M_PI / iterations;
}

void
RandomKnot::assignColors(void)
{
    // Initialize the color indices; -1 indicates an as-yet-unknown color.
    int color = mPrefs.technicolor() ? -1 : 0;
    for (int y = 0; y < mVSections; ++y) {
        for (int x = 0; x < mHSections; ++x) {
            mpSectionColors[BOT][y * mHSections + x] = color;
            mpSectionColors[TOP][y * mHSections + x] = color;
        }
    }
    ++color;

    // Assign colors to the sections by tracing all the 'strands' in the knot.
    for (int y = 0; y < mVSections; ++y) {
        for (int x = 0; x < mHSections; ++x) {
            if (mpSectionColors[TOP][y * mHSections + x] < 0) {
                // Assign a color to the top strand.
                if (traceColor(color, TOP, x, y, 0, 0)) {
                    ++color;
                }
            }

            if (mpSectionColors[BOT][y * mHSections + x] < 0) {
                // Assign a color to the bottom strand.
                switch (mpSectionTypes[y * mHSections + x]) {

                case D:
                case H:
                    if (traceColor(color, BOT, x, y, 0, 1)) {
                       ++color;
                    }
                    break;

                case V:
                    if (traceColor(color, BOT, x, y, 1, 0)) {
                        ++color;
                    }
                    break;

                case N:
                    break;
                }
            }
        }
    }

    // Generate the random colors.
    mpColors = new RandomColor[color];
    int hue = randomInteger(360);
    const int gamut = 90 + randomInteger(270);
    const int shift = gamut / color;
    for (int i = 0; i < color; ++i) {
        mpColors[i] = RandomColor(0.4, 0.9, 0.6, 1.0, 1.0, 1.0, hue);
        hue = (hue + shift) % 360;
    }
}

bool
RandomKnot::traceColor(int color, int layer, int x, int y, int dx, int dy)
{
    for (;;) {
        mpSectionColors[layer][y * mHSections + x] = color;

        // Hop across the corner indicated by dx/dy.
        switch (mpSectionCorners[(y+dy) * (mHSections+1) + x+dx]) {

        case D:
            x = (dx ? x+1 : x-1+mHSections) % mHSections;
            dx = 1-dx;
            y = (dy ? y+1 : y-1+mVSections) % mVSections;
            dy = 1-dy;
            break;

        case H:
            x = (dx ? x+1 : x-1+mHSections) % mHSections;
            dx = 1-dx;
            break;

        case V:
            y = (dy ? y+1 : y-1+mVSections) % mVSections;
            dy = 1-dy;
            break;

        case N:
            mpSectionColors[layer][y * mHSections + x] = 0;
            return false;
        }

        // Decide how to continue.
        switch (mpSectionTypes[y * mHSections + x]) {

        case D:
            dx = 1-dx;
            dy = 1-dy;
            layer = (dx + dy) % 2 ? BOT : TOP;
            break;

        case H:
            dx = 1-dx;
            layer = dy ? BOT : TOP;
            break;

        case V:
            dy = 1-dy;
            layer = dx ? BOT : TOP;
            break;

        case N:
            // This can't happen.
            abort();
        }

        if (mpSectionColors[layer][y * mHSections + x] == color) {
            // We're done with this strand.
            break;

        } else if (mpSectionColors[layer][y * mHSections + x] >= 0) {
            // This can't happen.
            abort();
        }
    }

    return true;
}
