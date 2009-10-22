//  A class representing a random horizontally tileable knot.
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

#ifndef HORIZONTALKNOT_H
#define HORIZONTALKNOT_H

#include "TiledKnot.h"

class HorizontalKnot : public TiledKnot
{
    typedef TiledKnot inherited;
public:
    HorizontalKnot(int windowWidth, int windowHeight);
    virtual ~HorizontalKnot(void);

private:
    HorizontalKnot(const HorizontalKnot &orig);
    HorizontalKnot &operator =(HorizontalKnot &orig);
};

#endif // HORIZONTALKNOT_H
