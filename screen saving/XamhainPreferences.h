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

#ifndef XAMHAINPREFERENCES_H
#define XAMHAINPREFERENCES_H

#include <objc/objc.h>
#include <OpenGL/gl.h>

class XamhainPreferences
{
public:
    XamhainPreferences(void);

    // Screen saving preferences.
    int
    numberOfKnots(void) const;
    bool
    technicolor(void) const;
    int
    ticksPerSecond(void) const;

    GLfloat
    minSize(void) const;
    GLfloat
    maxSize(void) const;

    GLfloat
    minSpeed(void) const;
    GLfloat
    maxSpeed(void) const;

    GLfloat
    minSpin(void) const;
    GLfloat
    maxSpin(void) const;

    GLfloat
    skewProbability(void) const;
    GLfloat
    spinProbability(void) const;

    // Knot engine preferences.
    int
    knotSubdivisions(void) const;

    GLfloat
    horizontalKnotProbability(void) const;
    GLfloat
    verticalKnotProbability(void) const;
    GLfloat
    closedKnotProbability(void) const;
    GLfloat
    circularKnotProbability(void) const;

    GLfloat
    sectionProbability1(void) const;
    GLfloat
    sectionProbability2(void) const;
    GLfloat
    cornerProbability1(void) const;
    GLfloat
    cornerProbability2(void) const;

    GLfloat
    broadKnotProbability(void) const;
    GLfloat
    hollowKnotProbability(void) const;

    GLfloat
    symmetricKnotProbability(void) const;
    GLfloat
    horizontalMirrorProbability(void) const;
    GLfloat
    verticalMirrorProbability(void) const;

    // ### TODO: colors

private:
    id mDefaults;      // actual screen saver defaults
};

#endif // XAMHAINPREFERENCES_H
