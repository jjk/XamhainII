//  Drawing style for a knot, combining fill and outline strokes.
//
//  Copyright © 2009  Jens Kilian
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

#ifndef KNOTSTYLE_H
#define KNOTSTYLE_H

#include "StrokeSet.h"

class KnotStyle
{
public:
    // Create a KnotStyle.
    KnotStyle(const char *const pName);

    // Inquiry functions.
    const StrokeSet &
    outline(void) const
    {
        return mOutline;
    }

    const StrokeSet &
    fill(void) const
    {
        return mFill;
    }

private:
    KnotStyle(const KnotStyle &);
    KnotStyle &operator =(const KnotStyle &);

    // Data members;
    const StrokeSet mOutline;
    const StrokeSet mFill;
};

#endif // KNOTSTYLE_H
