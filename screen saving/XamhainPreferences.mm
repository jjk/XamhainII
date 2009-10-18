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

#import "ScreenSaver/ScreenSaverDefaults.h"

namespace
{
    // Singleton instance.
    XamhainPreferences *gpInstance;
}

// Inquire the singleton preferences object.
const XamhainPreferences &
XamhainPreferences::instance(void)
{
    if (!gpInstance) {
        gpInstance = new XamhainPreferences;
    }

    return *gpInstance;
}

// Construct the singleton instance.
XamhainPreferences::XamhainPreferences(void)
:   mDefaults([ScreenSaverDefaults defaultsForModuleWithName: @"de.earrame.XamhainII"])
{
    // Register initial defaults.
    NSDictionary *factoryDefaults =
    [NSDictionary dictionaryWithObjectsAndKeys:
     @"NumberOfKnots",               @"8",
     @"Technicolor",                 @"YES",
     @"MinSize",                     @"0.2",
     @"MaxSize",                     @"0.5",
     @"MinSpeed",                    @"3.0",
     @"MaxSpeed",                    @"6.0",
     @"MinSpin",                     @"1.0",
     @"MaxSpin",                     @"5.0",
     @"SkewProbability",             @"0.8",
     @"SpinProbability",             @"0.8",
     @"KnotSubdivisions",            @"2",
     @"HorizontalKnotProbability",   @"0.1",
     @"VerticalKnotProbability",     @"0.2",
     @"ClosedKnotProbability",       @"0.5",
     @"CircularKnotProbability",     @"0.5",
     @"SectionProbability1",         @"0.06",
     @"SectionProbability2",         @"0.94",
     @"CornerProbability1",          @"0.2",
     @"CornerProbability2",          @"0.8",
     @"BroadKnotProbability",        @"0.5",
     @"HollowKnotProbability",       @"0.4",
     @"SymmetricKnotProbability",    @"0.8",
     @"HorizontalMirrorProbability", @"0.9",
     @"VerticalMirrorProbability",   @"0.9",
     NULL];

    [mDefaults registerDefaults: factoryDefaults];
}

// Implementation of inquiry functions.
int
XamhainPreferences::numberOfKnots(void) const
{
    return [mDefaults integerForKey: @"NumberOfKnots"];
}

bool
XamhainPreferences::technicolor(void) const
{
    return [mDefaults boolForKey: @"Technicolor"];
}

GLfloat
XamhainPreferences::minSize(void) const
{
    return [mDefaults floatForKey: @"MinSize"];
}

GLfloat
XamhainPreferences::maxSize(void) const
{
    return [mDefaults floatForKey: @"MaxSize"];
}

GLfloat
XamhainPreferences::minSpeed(void) const
{
    return [mDefaults floatForKey: @"MinSpeed"];
}

GLfloat
XamhainPreferences::maxSpeed(void) const
{
    return [mDefaults floatForKey: @"MaxSpeed"];
}

GLfloat
XamhainPreferences::minSpin(void) const
{
    return [mDefaults floatForKey: @"MinSpin"];
}

GLfloat
XamhainPreferences::maxSpin(void) const
{
    return [mDefaults floatForKey: @"MaxSpin"];
}

GLfloat
XamhainPreferences::skewProbability(void) const
{
    return [mDefaults floatForKey: @"SkewProbability"];
}

GLfloat
XamhainPreferences::spinProbability(void) const
{
    return [mDefaults floatForKey: @"SpinProbability"];
}

int
XamhainPreferences::knotSubdivisions(void) const
{
    return [mDefaults integerForKey: @"KnotSubdivisions"];
}

GLfloat
XamhainPreferences::horizontalKnotProbability(void) const
{
    return [mDefaults floatForKey: @"HorizontalKnotProbability"];
}

GLfloat
XamhainPreferences::verticalKnotProbability(void) const
{
    return [mDefaults floatForKey: @"VerticalKnotProbability"];
}

GLfloat
XamhainPreferences::closedKnotProbability(void) const
{
    return [mDefaults floatForKey: @"ClosedKnotProbability"];
}

GLfloat
XamhainPreferences::circularKnotProbability(void) const
{
    return [mDefaults floatForKey: @"CircularKnotProbability"];
}

GLfloat
XamhainPreferences::sectionProbability1(void) const
{
    return [mDefaults floatForKey: @"SectionProbability1"];
}

GLfloat
XamhainPreferences::sectionProbability2(void) const
{
    return [mDefaults floatForKey: @"SectionProbability2"];
}

GLfloat
XamhainPreferences::cornerProbability1(void) const
{
    return [mDefaults floatForKey: @"CornerProbability1"];
}

GLfloat
XamhainPreferences::cornerProbability2(void) const
{
    return [mDefaults floatForKey: @"CornerProbability2"];
}

GLfloat
XamhainPreferences::broadKnotProbability(void) const
{
    return [mDefaults floatForKey: @"BroadKnotProbability"];
}

GLfloat
XamhainPreferences::hollowKnotProbability(void) const
{
    return [mDefaults floatForKey: @"HollowKnotProbability"];
}

GLfloat
XamhainPreferences::symmetricKnotProbability(void) const
{
    return [mDefaults floatForKey: @"SymmetricKnotProbability"];
}

GLfloat
XamhainPreferences::horizontalMirrorProbability(void) const
{
    return [mDefaults floatForKey: @"HorizontalKnotProbability"];
}

GLfloat
XamhainPreferences::verticalMirrorProbability(void) const
{
    return [mDefaults floatForKey: @"VerticalKnotProbability"];
}
