//  A single primitive stroke, represented by a GL texture.
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

#ifndef STROKE_H
#define STROKE_H

#include <OpenGL/gl.h>

#include "Position.h"

class Stroke {
public:
    // Create a Stroke from one of our image files.
    Stroke(const char *name);

    // Destroy the associated texture.
    ~Stroke(void);

    // Draw the Stroke at the given location and size, transforming it
    // via the given matrix.  If the radius and angle are non-zero, the stroke
    // is warped into a segment of an annulus with the given midradius and
    // spanning the given angle; the center of the annulus is assumed to lie
    // at (where.x - radius, where.y).
    void
    draw(Position where, GLfloat size, GLfloat radius, GLfloat angle,
         const GLint transform[4]) const;

private:
    Stroke(const Stroke &);
    Stroke &operator =(const Stroke &);

    // Data members.
    const int mSubdivisions;    // subdivisions for warping
    GLuint mTexture;            // ID of stroke texture
};

#endif // STROKE_H
