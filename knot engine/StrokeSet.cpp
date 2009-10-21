//  A StrokeSet contains the 10 basic strokes from which knots are built,
//  plus an additional stroke used in filling in corners.
//
//  Copyright © 2003-2009  Jens Kilian
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

#include "StrokeSet.h"

#include "Stroke.h"

#define StaticStroke(stroke, shape, type) \
    static const Stroke Stroke_##stroke(#shape "_" #type "_" #stroke ".pdf");

#define StaticStrokeSet(name, shape, type)                                   \
    const StrokeSet &                                                        \
    StrokeSet::name(void)                                                    \
    {                                                                        \
        StaticStroke(DDD, shape, type);                                      \
        StaticStroke(DHD, shape, type);                                      \
        StaticStroke(DHH, shape, type);                                      \
        StaticStroke(DHV, shape, type);                                      \
        StaticStroke(HDD, shape, type);                                      \
        StaticStroke(HDH, shape, type);                                      \
        StaticStroke(HDV, shape, type);                                      \
        StaticStroke(HHH, shape, type);                                      \
        StaticStroke(HHV, shape, type);                                      \
        StaticStroke(HVV, shape, type);                                      \
        StaticStroke(corner, shape, type);                                   \
                                                                             \
        static const Stroke *const pStrokes[NumStrokes] = {                  \
            &Stroke_DDD, &Stroke_DHD, &Stroke_DHH, &Stroke_DHV, &Stroke_HDD, \
            &Stroke_HDH, &Stroke_HDV, &Stroke_HHH, &Stroke_HHV, &Stroke_HVV, \
            &Stroke_corner,                                                  \
        };                                                                   \
        static const StrokeSet theSet(pStrokes);                             \
                                                                             \
        return theSet;                                                       \
    }

StaticStrokeSet(broadFill, broad, fill)
StaticStrokeSet(broadOutline, broad, outline)
StaticStrokeSet(slenderFill, slender, fill)
StaticStrokeSet(slenderOutline, slender, outline)
