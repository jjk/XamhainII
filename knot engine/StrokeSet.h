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

#ifndef STROKESET_H
#define STROKESET_H

#include <string>

class Stroke;

class StrokeSet {
public:
    // Stroke types.
    enum {
        DDD, DHD, DHH, DHV,
        HDD, HDH, HDV, HHH, HHV, HVV,
        Corner,
        NumStrokes
    };

    // Construct a set of strokes of a given style and type.
    StrokeSet(const char *const pStyle, const char *const pType);

    // Destroy the StrokeSet.
    ~StrokeSet(void);

    // Return a Stroke of the given type.
    const Stroke &
    operator [](unsigned int index) const;

private:
    StrokeSet(const StrokeSet &);
    StrokeSet &operator =(const StrokeSet &);

    // Data members.
    const ::std::string mPrefix;
    mutable const Stroke *mpStrokes[NumStrokes];
};

#endif // STROKESET_H
