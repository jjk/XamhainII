//  XamhainII screen saver preferences.
//
//  Copyright © 2000-2009, Jens Kilian.
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

#include "XamhainPreferences.h"

#include <algorithm>
using namespace ::std;

#import "XamhainUserDefaultsController.h"


// Construct a preferences object - which is actually just a wrapper.
XamhainPreferences::XamhainPreferences(void)
:   mDefaults([[XamhainUserDefaultsController sharedUserDefaultsController] defaults])
{
    // empty
}

// Implementation of inquiry functions.
int
XamhainPreferences::numberOfKnots(void) const
{
    return max((NSInteger)1, [mDefaults integerForKey: @"NumberOfKnots"]);
}

bool
XamhainPreferences::technicolor(void) const
{
    return [mDefaults boolForKey: @"Technicolor"];
}

int
XamhainPreferences::ticksPerSecond(void) const
{
    return max((NSInteger)1, [mDefaults integerForKey: @"TicksPerSecond"]);
}

GLfloat
XamhainPreferences::minSize(void) const
{
    return min([mDefaults floatForKey: @"MinSize"],
               [mDefaults floatForKey: @"MaxSize"]);
}

GLfloat
XamhainPreferences::maxSize(void) const
{
    return max([mDefaults floatForKey: @"MinSize"],
               [mDefaults floatForKey: @"MaxSize"]);
}

GLfloat
XamhainPreferences::minSpeed(void) const
{
    return min([mDefaults floatForKey: @"MinSpeed"],
               [mDefaults floatForKey: @"MaxSpeed"]);
}

GLfloat
XamhainPreferences::maxSpeed(void) const
{
    return max([mDefaults floatForKey: @"MinSpeed"],
               [mDefaults floatForKey: @"MaxSpeed"]);
}

GLfloat
XamhainPreferences::minSpin(void) const
{
    return min([mDefaults floatForKey: @"MinSpin"],
               [mDefaults floatForKey: @"MaxSpin"]);
}

GLfloat
XamhainPreferences::maxSpin(void) const
{
    return max([mDefaults floatForKey: @"MinSpin"],
               [mDefaults floatForKey: @"MaxSpin"]);
}

GLfloat
XamhainPreferences::skewProbability(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"SkewProbability"]), 1.0f);
}

GLfloat
XamhainPreferences::spinProbability(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"SpinProbability"]), 1.0f);
}

int
XamhainPreferences::knotSubdivisions(void) const
{
    return max((NSInteger)1, [mDefaults integerForKey: @"KnotSubdivisions"]);
}

GLfloat
XamhainPreferences::horizontalKnotProbability(void) const
{
    return min(max(0.0f,
                   [mDefaults floatForKey: @"HorizontalKnotProbability"]
                   / totalKnotProbability()),
               1.0f);
}

GLfloat
XamhainPreferences::verticalKnotProbability(void) const
{
    return min(max(0.0f,
                   [mDefaults floatForKey: @"VerticalKnotProbability"]
                   / totalKnotProbability()),
               1.0f);
}

GLfloat
XamhainPreferences::closedKnotProbability(void) const
{
    return min(max(0.0f,
                   [mDefaults floatForKey: @"ClosedKnotProbability"]
                   / totalKnotProbability()),
               1.0f);
}

GLfloat
XamhainPreferences::circularKnotProbability(void) const
{
    return min(max(0.0f,
                   [mDefaults floatForKey: @"CircularKnotProbability"]
                   / totalKnotProbability()),
               1.0f);
}

GLfloat
XamhainPreferences::sectionProbability1(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"SectionProbability1"]), 1.0f);
}

GLfloat
XamhainPreferences::sectionProbability2(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"SectionProbability2"]), 1.0f);
}

GLfloat
XamhainPreferences::cornerProbability1(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"CornerProbability1"]), 1.0f);
}

GLfloat
XamhainPreferences::cornerProbability2(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"CornerProbability2"]), 1.0f);
}

GLfloat
XamhainPreferences::broadKnotProbability(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"BroadKnotProbability"]), 1.0f);
}

GLfloat
XamhainPreferences::hollowKnotProbability(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"HollowKnotProbability"]), 1.0f);
}

GLfloat
XamhainPreferences::symmetricKnotProbability(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"SymmetricKnotProbability"]), 1.0f);
}

GLfloat
XamhainPreferences::horizontalMirrorProbability(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"HorizontalMirrorProbability"]), 1.0f);
}

GLfloat
XamhainPreferences::verticalMirrorProbability(void) const
{
    return min(max(0.0f, [mDefaults floatForKey: @"VerticalMirrorProbability"]), 1.0f);
}

GLfloat
XamhainPreferences::totalKnotProbability(void) const
{
    return [mDefaults floatForKey: @"HorizontalKnotProbability"]
    +      [mDefaults floatForKey: @"VerticalKnotProbability"]
    +      [mDefaults floatForKey: @"ClosedKnotProbability"]
    +      [mDefaults floatForKey: @"CircularKnotProbability"];
}
