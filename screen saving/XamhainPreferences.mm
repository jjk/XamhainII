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
    // TODO - register initial defaults.
}

// Implementation of inquiry functions.
int
XamhainPreferences::numberOfKnots(void) const
{
    return 0;
}

bool
XamhainPreferences::technicolor(void) const
{
    return false;
}

GLfloat
XamhainPreferences::minSize(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::maxSize(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::minSpeed(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::maxSpeed(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::minSpin(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::maxSpin(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::skewProbability(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::spinProbability(void) const
{
    return 0;
}

int
XamhainPreferences::knotSubdivisions(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::horizontalKnotProbability(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::verticalKnotProbability(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::closedKnotProbability(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::circularKnotProbability(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::sectionProbability1(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::sectionProbability2(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::cornerProbability1(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::cornerProbability2(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::broadKnotProbability(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::hollowKnotProbability(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::symmetricKnotProbability(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::horizontalMirrorProbability(void) const
{
    return 0;
}

GLfloat
XamhainPreferences::verticalMirrorProbability(void) const
{
    return 0;
}
