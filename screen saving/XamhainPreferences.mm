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

#import <ScreenSaver/ScreenSaverDefaults.h>


@interface XamhainScreenSaverDefaults
{
    // empty
}

+ (NSUserDefaults *) sharedDefaults;

@end

namespace
{
    NSUserDefaults *gInstance = nil;
}

@implementation XamhainScreenSaverDefaults

+ (void) initialize
{
    gInstance = [ScreenSaverDefaults defaultsForModuleWithName: @"de.earrame.XamhainII"];

    // Register initial defaults.
    NSDictionary *factoryDefaults =
    [NSDictionary dictionaryWithObjectsAndKeys:
     @"8",    @"NumberOfKnots",
     @"YES",  @"Technicolor",
     @"60",   @"TicksPerSecond",
     @"0.2",  @"MinSize",
     @"0.5",  @"MaxSize",
     @"3.0",  @"MinSpeed",
     @"6.0",  @"MaxSpeed",
     @"1.0",  @"MinSpin",
     @"5.0",  @"MaxSpin",
     @"0.8",  @"SkewProbability",
     @"0.8",  @"SpinProbability",
     @"2",    @"KnotSubdivisions",
     @"0.1",  @"HorizontalKnotProbability",
     @"0.2",  @"VerticalKnotProbability",
     @"0.5",  @"ClosedKnotProbability",
     @"0.5",  @"CircularKnotProbability",
     @"0.06", @"SectionProbability1",
     @"0.94", @"SectionProbability2",
     @"0.2",  @"CornerProbability1",
     @"0.8",  @"CornerProbability2",
     @"0.5",  @"BroadKnotProbability",
     @"0.4",  @"HollowKnotProbability",
     @"0.8",  @"SymmetricKnotProbability",
     @"0.9",  @"HorizontalMirrorProbability",
     @"0.9",  @"VerticalMirrorProbability",
     NULL];

    [gInstance registerDefaults: factoryDefaults];
}

+ (NSUserDefaults *) sharedDefaults
{
    return gInstance;
}

@end

// Construct a preferences object - which is actually just a wrapper.
XamhainPreferences::XamhainPreferences(void)
:   mDefaults([XamhainScreenSaverDefaults sharedDefaults])
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
