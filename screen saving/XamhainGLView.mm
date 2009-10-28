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
#include "KnotStyle.h"
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

- (id) initWithFrame: (NSRect)frame
{
    self = [super initWithFrame: frame];
    if (self) {
        mpPrefs = new XamhainPreferences;

        mpSlenderStyle = mpBroadStyle = 0;

        mppKnots = 0;
    }

    return self;
}

- (void) startAnimation
{
    mpBroadStyle = new KnotStyle("broad");
    mpSlenderStyle = new KnotStyle("slender");

    mNumberOfKnots = mpPrefs->numberOfKnots();
    mppKnots = new RandomKnot *[mNumberOfKnots];
    fill(mppKnots, mppKnots + mNumberOfKnots, (RandomKnot *)0);
}

- (void) stopAnimation
{
    if (mppKnots) {
        for (int i = 0; i < mNumberOfKnots; ++i) {
            delete mppKnots[i];
        }
        delete [] mppKnots;
        mppKnots = 0;
    }

    delete mpSlenderStyle;
    delete mpBroadStyle;
    mpSlenderStyle = mpBroadStyle = 0;
}

- (void) finalize
{
    delete mpPrefs;

    [super finalize];
}

- (void) prepareOpenGL
{
    const GLint one = 1;
    [[self openGLContext] setValues: &one forParameter: NSOpenGLCPSwapInterval];

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

- (void) reshape
{
    const NSSize size = [self bounds].size;
    const int width = size.width;
    const int height = size.height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

- (void) drawRect: (NSRect)dirtyRect
{
    (void)dirtyRect;

    glClear(GL_COLOR_BUFFER_BIT);

    if (mppKnots) {
        const NSSize size = [self bounds].size;
        const int width = size.width;
        const int height = size.height;

        for (int i = 0; i < mNumberOfKnots; ++i) {
            if (!mppKnots[i]) {
                // Determine knot style.
                const KnotStyle &style =
                randomFloat() < mpPrefs->broadKnotProbability()
                ? *mpBroadStyle
                : *mpSlenderStyle;

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
                        mppKnots[i] = new ClosedKnot(style, width, height);
                        break;

                    case kCircular:
                        mppKnots[i] = new CircularKnot(style, width, height);
                        break;

                    case kHorizontal:
                        mppKnots[i] = new HorizontalKnot(style, width, height);
                        break;

                    case kVertical:
                        mppKnots[i] = new VerticalKnot(style, width, height);
                        break;
                }
            }

            if (!mppKnots[i]->animate()) {
                delete mppKnots[i];
                mppKnots[i] = 0;
            }
        }
    }

    [[self openGLContext] flushBuffer];
}

@end
