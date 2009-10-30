//  XamhainII screen saver view.
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

#import "XamhainView.h"

#import "XamhainGLView.h"
#include "XamhainPreferences.h"
#import "XamhainUserDefaultsController.h"


@implementation XamhainView

- (id) initWithFrame: (NSRect)frame isPreview: (BOOL)isPreview
{
    self = [super initWithFrame: frame isPreview: isPreview];
    if (self) {
        XamhainPreferences prefs;
        [self setAnimationTimeInterval: 1.0/prefs.ticksPerSecond()];

        const NSRect childFrame =
            NSOffsetRect(frame, -frame.origin.x, -frame.origin.y);
        mpGLView = [[XamhainGLView alloc] initWithFrame: childFrame];
        if (mpGLView) {
            [self addSubview: mpGLView];

        } else {
            NSLog(@"Failed to create XamhainGLView.");
        }
    } else {
        NSLog(@"Failed to create XamhainView");
    }

    return self;
}

- (void) startAnimation
{
    [super startAnimation];
    [mpGLView startAnimation];
}

- (void) stopAnimation
{
    [super stopAnimation];
    [mpGLView stopAnimation];
}

- (void) animateOneFrame
{
    [mpGLView setNeedsDisplay: YES];
}

- (BOOL) hasConfigureSheet
{
    return YES;
}

- (NSWindow *) configureSheet
{
    return [[XamhainUserDefaultsController sharedUserDefaultsController]
            configureSheet];
}

@end
