//  XamhainII user defaults controller.
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

// The only reason for defining our own version of the standard
// NSUserDefaultsController class is that we can't use an instance
// of the original one which is allocated in our nib file.  It appears
// that Interface Builder only supports the standard (shared) user
// defaults, and not the weird individual ones that the screen saver
// framework deals out.  So we need to create our own controller and
// pass it to the nib as the File's Owner.
//
// Alternatively we could have set up our bindings by hand.  Meh.
//
// See also http://jwz.livejournal.com/756713.html?thread=14516713#t14516713

#import "XamhainUserDefaultsController.h"

#import <ScreenSaver/ScreenSaverDefaults.h>


namespace
{
    const NSString *kBundleName = @"de.earrame.XamhainII";

    XamhainUserDefaultsController *gpInstance = nil;
}

@implementation XamhainUserDefaultsController

+ (void) initialize
{
    if (self == [XamhainUserDefaultsController class]) {
        // THIS is causing all the trouble.
        NSUserDefaults *defaults = [ScreenSaverDefaults defaultsForModuleWithName: kBundleName];

        // Load initial defaults and register them.
        NSBundle *bundle = [NSBundle bundleWithIdentifier: kBundleName];
        NSString *path = [bundle pathForResource: @"defaults" ofType: @"plist"];
        assert(path != nil);

        NSDictionary *factoryDefaults = [NSDictionary dictionaryWithContentsOfFile: path];
        assert(factoryDefaults != nil);

        [defaults registerDefaults: factoryDefaults];

        // Create the shared user defaults controller.
        gpInstance = [[XamhainUserDefaultsController alloc]
                      initWithDefaults: defaults
                      initialValues: factoryDefaults];
        [gpInstance setAppliesImmediately: NO];

        // Load our nib file.
        gpInstance->mpNib = [[NSNib alloc] initWithNibNamed: @"XamhainConfigureSheet"
                                                     bundle: bundle];
    }
}

+ (id) sharedUserDefaultsController
{
    return gpInstance;
}

- (NSWindow *) configureSheet
{
    if (!mpConfigureSheet) {
        if (![mpNib instantiateNibWithOwner: self topLevelObjects: nil]) {
            NSLog(@"Could not load configuration sheet.");
        }
    }

    return mpConfigureSheet;
}

- (IBAction) save: (id)sender
{
    [super save: sender];

    if (mpConfigureSheet) {
        [NSApp endSheet: mpConfigureSheet returnCode: NSOKButton];
        [mpConfigureSheet close];
    }
}

- (IBAction) revert: (id)sender
{
    [super revert: sender];

    if (mpConfigureSheet) {
        [NSApp endSheet: mpConfigureSheet returnCode: NSCancelButton];
        [mpConfigureSheet close];
    }
}

@end
