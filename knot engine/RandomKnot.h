//  Abstract base class for creating random knots.
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

#ifndef RANDOMKNOT_H
#define RANDOMKNOT_H

#include <OpenGL/gl.h>

#include "KnotSection.h"
class KnotStyle;
#include "Position.h"
#include "RandomColor.h"
class StrokeSet;
#include "XamhainPreferences.h"

class RandomKnot
{
public:
    RandomKnot(const KnotStyle &knotStyle,
               int windowWidth, int windowHeight, int maxSections);
    virtual ~RandomKnot(void);

    // Perform a single animation cycle; return 'false' when finished.
    bool
    animate(void);

protected:
    // Return display list for drawing the basic knot.
    GLuint
    displayList(void) const;

    // Draw the basic knot at the origin (to set up the display list).
    virtual void
    drawBasicKnot(void) const = 0;

    // Enforce symmetries in the random arrays.
    void
    enforceHorizontalSymmetry(bool mirror);
    void
    enforceVerticalSymmetry(bool mirror);

    // Calculate animation parameters given the knot's size.
    void
    prepareAnimation(Position extent, bool xRepeat = false, bool yRepeat = false);

    // Assign colors to the knot.
    void
    assignColors(void);

    // Inquire knot data.
    Direction
    sectionType(int x, int y) const
    {
        return mpSectionTypes[y * mHSections + x];
    }
    Direction &
    sectionType(int x, int y)
    {
        return mpSectionTypes[y * mHSections + x];
    }

    Direction
    sectionCorner(int x, int y) const
    {
        return mpSectionCorners[y * (mHSections + 1) + x];
    }
    Direction &
    sectionCorner(int x, int y)
    {
        return mpSectionCorners[y * (mHSections + 1) + x];
    }

    const GLfloat *
    sectionColor(int layer, int x, int y) const
    {
        return mpColors[mpSectionColors[layer][y * mHSections + x]];
    }
    const GLfloat *
    leftTopCornerColor(int x, int y) const
    {
        y = (y - 1 + mVSections) % mVSections;
        if (sectionType(x, y) != V) {
            return sectionColor(BOT, x, y);
        } else {
            return sectionColor(TOP, x, y);
        }
    }
    const GLfloat *
    rightBottomCornerColor(int x, int y) const
    {
        y = (y + 1) % mVSections;
        if (sectionType(x, y) != H) {
            return sectionColor(BOT, x, y);
        } else {
            return sectionColor(TOP, x, y);
        }
    }

    // Data members.
    XamhainPreferences mPrefs;         // user preferences
    const int mWindowWidth;            // window size
    const int mWindowHeight;
    const int mHSections;              // horizontal #sections
    const int mVSections;              // vertical #sections
    const StrokeSet &mOutlineStrokes;  // knot properties
    const StrokeSet &mFillStrokes;
    bool mHollow;

private:
    RandomKnot(const RandomKnot &orig);
    RandomKnot &operator =(RandomKnot &orig);

    // Draw the (possibly replicated) knot.
    virtual void
    draw(Position where, GLfloat angle) const = 0;

    // Trace a 'strand' of the knot and assign a color to it.
    bool
    traceColor(int color, int layer, int x, int y, int dx, int dy);

    // Data members.
    Direction *mpSectionTypes;   // types of sections
    Direction *mpSectionCorners; // corner directions
    int *mpSectionColors[2];     // color indices (two per section)
    RandomColor *mpColors;       // colors
    Position mBasePosition;      // animation data
    Position mDirection;
    GLfloat mSpeed;
    GLfloat mAngle;
    GLfloat mSpin;
    GLfloat mTime;
    GLfloat mMaxTime;
    mutable GLuint mDisplayList; // display list caching the basic knot
};

#endif // RANDOMKNOT_H
