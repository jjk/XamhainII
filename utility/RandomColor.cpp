//  Select a color of random hue, within a given range of lightness,
//  saturation and transparency.
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

#include "RandomColor.h"

#include <OpenGL/gl.h>

#include "RandomNumbers.h"

// We could of course use the native OS X color management services instead.
// Muahaha.  Just kidding.

namespace
{
    inline GLfloat
    rgb(GLfloat q1, GLfloat q2, int hue)
    {
        hue = (hue + 360) % 360;
        if (hue < 60) {
            return q1 + (q2-q1) * hue / 60.0;

        } else if (hue < 180) {
            return q2;

        } else if (hue < 240) {
            return q1 + (q2-q1) * (240 - hue) / 60.0;

        } else {
            return q1;
        }
    }
}

RandomColor::RandomColor(
    GLfloat minL, GLfloat maxL,
    GLfloat minS, GLfloat maxS,
    GLfloat minT, GLfloat maxT,
    int hue)
{
    if (hue < 0) {
        hue = randomInteger(360);
    } else {
        hue %= 360;
    }

    GLfloat lightness  = minL + randomFloat() * (maxL-minL);
    GLfloat saturation = minS + randomFloat() * (maxS-minS);

    // HLS to RGB conversion.  Sheer magic, don't ask me :-)
    GLfloat p2 = (lightness <= 0.5)
        ? lightness * (saturation + 1.0)
        : lightness + saturation - lightness*saturation;
    GLfloat p1 = 2.0*lightness - p2;

    if (saturation == 0.0) {
        mColor[0] = mColor[1] = mColor[2] = lightness;
    } else {
        mColor[0] = rgb(p1, p2, hue + 120);
        mColor[1] = rgb(p1, p2, hue);
        mColor[2] = rgb(p1, p2, hue - 120);
    }

    mColor[3] = minT + randomFloat() * (maxT-minT);
}
