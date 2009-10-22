//  A class representing a random vertically tileable knot.
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

#ifndef VERTICALKNOT_H
#define VERTICALKNOT_H

#include "TiledKnot.h"

class VerticalKnot : public TiledKnot
{
    typedef TiledKnot inherited;
public:
    VerticalKnot(int windowWidth, int windowHeight);
    virtual ~VerticalKnot(void);

private:
    VerticalKnot(const VerticalKnot &orig);
    VerticalKnot &operator =(VerticalKnot &orig);
};

#endif // VERTICALKNOT_H
