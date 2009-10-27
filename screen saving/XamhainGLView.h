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

#import <AppKit/NSOpenGLView.h>

class RandomKnot;
class XamhainPreferences;


@interface XamhainGLView : NSOpenGLView
{
    XamhainPreferences *mpPrefs; // user defaults
    RandomKnot **mppKnots;       // knots being animated
}

@end
