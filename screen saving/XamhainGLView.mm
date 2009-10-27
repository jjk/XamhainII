//  XamhainII OpenGL view.
//
//  Copyright © 2009, Jens Kilian.
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

#import "XamhainGLView.h"

#include <algorithm>
using namespace ::std;

#include <OpenGL/gl.h>

#include "CircularKnot.h"
#include "ClosedKnot.h"
#include "HorizontalKnot.h"
#include "RandomNumbers.h"
#include "VerticalKnot.h"


namespace
{
    // Knot types.
    enum KnotType {
        kClosed,
        kCircular,
        kHorizontal,
        kVertical
    };
}

@implementation XamhainGLView

+ (NSOpenGLPixelFormat *) defaultPixelFormat
{
    static const NSOpenGLPixelFormatAttribute attributes[] =
    {
        NSOpenGLPFADoubleBuffer,
        0
    };

    return [[NSOpenGLPixelFormat alloc] initWithAttributes: attributes];
}

- (XamhainGLView *) initWithFrame: (NSRect)frame
{
    self = [super initWithFrame: frame];
    if (self) {
        mpPrefs = new XamhainPreferences;
        mppKnots = new RandomKnot *[mpPrefs->numberOfKnots()];
        fill(mppKnots, mppKnots + mpPrefs->numberOfKnots(), (RandomKnot *)0);
    }

    return self;
}

- (void) finalize
{
    if (mppKnots) {
        for (int i = 0; i < mpPrefs->numberOfKnots(); ++i) {
            delete mppKnots[i];
        }
        delete [] mppKnots;
    }
    delete mpPrefs;

    [super finalize];
}

- (void) prepareOpenGL
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

- (void) drawRect: (NSRect)bounds
{
    const int width = bounds.size.width;
    const int height = bounds.size.height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < mpPrefs->numberOfKnots(); ++i) {
        if (!mppKnots[i]) {
            // Determine knot type.
            KnotType type = kCircular;
            GLfloat p = randomFloat();

            if ((p -= mpPrefs->horizontalKnotProbability()) < 0.0) {
                type = kHorizontal;
            } else if ((p -= mpPrefs->verticalKnotProbability()) < 0.0) {
                type = kVertical;
            } else if ((p -= mpPrefs->closedKnotProbability()) < 0.0) {
                type = kClosed;
            }

            switch (type) {

            case kClosed:
                mppKnots[i] = new ClosedKnot(width, height);
                break;

            case kCircular:
                mppKnots[i] = new CircularKnot(width, height);
                break;

            case kHorizontal:
                mppKnots[i] = new HorizontalKnot(width, height);
                break;

            case kVertical:
                mppKnots[i] = new VerticalKnot(width, height);
                break;
            }
        }

        if (!mppKnots[i]->animate()) {
            delete mppKnots[i];
            mppKnots[i] = 0;
        }
    }

    [[self openGLContext] flushBuffer];
}

@end
