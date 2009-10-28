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

#include <cassert>
#include <string>
using namespace ::std;

#include "Stroke.h"

namespace
{
    static const string kShape[StrokeSet::NumStrokes] =
    {
        "DDD", "DHD", "DHH", "DHV",
        "HDD", "HDH", "HDV", "HHH", "HHV", "HVV",
        "corner"
    };
}

StrokeSet::StrokeSet(const char *const pStyle, const char *const pType)
:   mPrefix(string(pStyle) + string("_") + string(pType) + string("_"))
{
    for (int i = 0; i < NumStrokes; ++i) {
        mpStrokes[i] = 0;
    }
}

StrokeSet::~StrokeSet(void)
{
    for (int i = 0; i < NumStrokes; ++i) {
        delete mpStrokes[i];
    }
}

const Stroke &
StrokeSet::operator [](unsigned int index) const
{
    assert(index < NumStrokes);
    if (!mpStrokes[index]) {
        const string name = mPrefix + kShape[index];
        mpStrokes[index] = new Stroke(name.c_str());
    }
    return *mpStrokes[index];
}
