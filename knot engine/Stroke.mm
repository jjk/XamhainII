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

#include "Stroke.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "Position.h"
#include "XamhainPreferences.h"

namespace
{
    // Nominal size of a texture.
    const GLsizei kTextureSize = 64;

    // Internal texture format.
    const GLenum kTextureFormat = GL_ALPHA4;

    // Cache for values of trigonometric functions.
    class TrigFunctionCache
    {
    public:
        TrigFunctionCache(const GLfloat arcLength)
        :   mSubdivisions(XamhainPreferences().knotSubdivisions()),
            mpSin(new GLfloat[mSubdivisions]),
            mpCos(new GLfloat[mSubdivisions])
        {
            for (int i = 0; i < mSubdivisions; ++i) {
                const GLfloat arg = (i+1) * arcLength * 0.5 / mSubdivisions;
                mpSin[i] = ::sin(arg);
                mpCos[i] = ::cos(arg);
            }
        }
        ~TrigFunctionCache(void)
        {
            delete [] mpSin;
            delete [] mpCos;
            mpSin = mpCos = 0;
        }

        GLfloat
        sin(const int index) const
        {
            if (index) {
                return (index < 0) ? -mpSin[-index-1] : mpSin[index-1];
            }
            return 0.0;
        }

        GLfloat
        cos(const int index) const
        {
            if (index) {
                return (index < 0) ? mpCos[-index-1] : mpCos[index-1];
            }
            return 1.0;
        }

    private:
        TrigFunctionCache(const TrigFunctionCache &);
        TrigFunctionCache &operator =(const TrigFunctionCache &);

        // Data members.
        const int mSubdivisions;
        GLfloat *mpSin;
        GLfloat *mpCos;
    };

    // Load an image resource and convert it to a bitmap.
    NSBitmapImageRep *
    loadImage(const char *const name)
    {
        // Load the (PDF) image.
        NSImage *image = [NSImage imageNamed:
                          [NSString stringWithCString: name
                                             encoding: NSASCIIStringEncoding]];
        assert(image != nil);

        // Create a bitmap of the desired size.
        NSBitmapImageRep *bitmap =
        [[NSBitmapImageRep alloc]
         initWithBitmapDataPlanes: NULL
         pixelsWide: kTextureSize
         pixelsHigh: kTextureSize
         bitsPerSample: 8
         samplesPerPixel: 1
         hasAlpha: NO
         isPlanar: NO
         colorSpaceName: NSDeviceWhiteColorSpace
         bytesPerRow: 0
         bitsPerPixel: 0];

        // Draw the image at the desired size.
        [NSGraphicsContext saveGraphicsState];
        [NSGraphicsContext setCurrentContext:
         [NSGraphicsContext graphicsContextWithBitmapImageRep: bitmap]];

        const NSSize size = [image size];
        [image drawInRect: NSMakeRect(0.0, 0.0, kTextureSize, kTextureSize)
                 fromRect: NSMakeRect(0.0, 0.0, size.width, size.height)
                operation: NSCompositeCopy
                 fraction: 1.0];

        [NSGraphicsContext restoreGraphicsState];

        return bitmap;
    }
}

Stroke::Stroke(const char *const name)
:   mSubdivisions(XamhainPreferences().knotSubdivisions()){
    // Load image resource.
    NSBitmapImageRep *bitmap = loadImage(name);

    // Create a texture object for the stroke.
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, [bitmap pixelsWide]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    gluBuild2DMipmaps(GL_TEXTURE_2D, kTextureFormat,
                      kTextureSize, kTextureSize,
                      GL_ALPHA, GL_UNSIGNED_BYTE, [bitmap bitmapData]);
}

Stroke::~Stroke(void)
{
    glDeleteTextures(1, &mTexture);
    mTexture = 0;
}

void
Stroke::Draw(Position where, GLfloat size, GLfloat radius, GLfloat angle,
             const GLint transform[4]) const
{
    if (radius <= 0.0 || angle <= 0.0) {
        size *= 0.5f;

        const GLfloat t0 = size * transform[0];
        const GLfloat t1 = size * transform[1];
        const GLfloat t2 = size * transform[2];
        const GLfloat t3 = size * transform[3];

        const GLfloat r =  1.0f;
        const GLfloat b = -1.0f;

        glBindTexture(GL_TEXTURE_2D, mTexture);
        glBegin(GL_POLYGON);
        {
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(where.x - t0 + b * t1, where.y - t2 + b * t3);

            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(where.x + r * t0 + b * t1, where.y + r * t2 + b * t3);

            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(where.x + r * t0 + t1, where.y + r * t2 + t3);

            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(where.x - t0 + t1, where.y - t2 + t3);
        }
        glEnd();

    } else {
        size = size * 0.5 / mSubdivisions;

        const GLint r =  mSubdivisions;
        const GLint b = -mSubdivisions;

        const TrigFunctionCache cache(angle);

        glBindTexture(GL_TEXTURE_2D, mTexture);
        glBegin(GL_QUADS);
        {
            for (GLint x = -mSubdivisions; x < r; ++x) {
                for (GLint y = b; y < mSubdivisions; ++y) {
                    const GLint x0 =     x * transform[0] +     y * transform[1];
                    const GLint y0 =     x * transform[2] +     y * transform[3];
                    const GLint x1 = (x+1) * transform[0] +     y * transform[1];
                    const GLint y1 = (x+1) * transform[2] +     y * transform[3];
                    const GLint x2 = (x+1) * transform[0] + (y+1) * transform[1];
                    const GLint y2 = (x+1) * transform[2] + (y+1) * transform[3];
                    const GLint x3 =     x * transform[0] + (y+1) * transform[1];
                    const GLint y3 =     x * transform[2] + (y+1) * transform[3];

                    const GLfloat r0 = size * x0 + radius;
                    const GLfloat r1 = size * x1 + radius;
                    const GLfloat r2 = size * x2 + radius;
                    const GLfloat r3 = size * x3 + radius;

                    glTexCoord2f(
                        (GLfloat)(x+mSubdivisions) / (GLfloat)(r+mSubdivisions),
                        (GLfloat)(mSubdivisions-y) / (GLfloat)(mSubdivisions-b));
                    glVertex2f(where.x + r0 * cache.cos(y0) - radius,
                               where.y + r0 * cache.sin(y0));

                    glTexCoord2f(
                        (GLfloat)(x+1+mSubdivisions) / (GLfloat)(r+mSubdivisions),
                        (GLfloat)(mSubdivisions-y) / (GLfloat)(mSubdivisions-b));
                    glVertex2f(where.x + r1 * cache.cos(y1) - radius,
                               where.y + r1 * cache.sin(y1));

                    glTexCoord2f(
                        (GLfloat)(x+1+mSubdivisions) / (GLfloat)(r+mSubdivisions),
                        (GLfloat)(mSubdivisions-y-1) / (GLfloat)(mSubdivisions-b));
                    glVertex2f(where.x + r2 * cache.cos(y2) - radius,
                               where.y + r2 * cache.sin(y2));

                    glTexCoord2f(
                        (GLfloat)(x+mSubdivisions) / (GLfloat)(r+mSubdivisions),
                        (GLfloat)(mSubdivisions-y-1) / (GLfloat)(mSubdivisions-b));
                    glVertex2f(where.x + r3 * cache.cos(y3) - radius,
                               where.y + r3 * cache.sin(y3));
                }
            }
        }
        glEnd();
    }
}
