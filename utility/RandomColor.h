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

#ifndef RANDOMCOLOR_H
#define RANDOMCOLOR_H

#include <OpenGL/gl.h>

class RandomColor {
public:
    RandomColor(void)
    {
        // empty
    }

    RandomColor(GLfloat minL, GLfloat maxL,
                GLfloat minS, GLfloat maxS,
                GLfloat minT, GLfloat maxT,
                int hue = -1);

    RandomColor(const RandomColor &orig)
    {
        for (int i = 0; i < 4; ++i) {
            mColor[i] = orig.mColor[i];
        }
    }

    RandomColor &
    operator =(const RandomColor &orig)
    {
        for (int i = 0; i < 4; ++i) {
            mColor[i] = orig.mColor[i];
        }
        return *this;
    }

    operator const GLfloat *(void) const
    {
        return mColor;
    }

private:
    GLfloat mColor[4];
};

#endif // RANDOMCOLOR_H
