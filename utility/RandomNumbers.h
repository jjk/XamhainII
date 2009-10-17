//  Utility functions for calculating random numbers.
//
//  Copyright (c) 2000-2009  Jens Kilian
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

#ifndef RANDOMNUMBERS_H
#define RANDOMNUMBERS_H

#include <cstdlib>

// We could use the random routines from the ScreenSaver framework,
// but (1) they return values from closed intervals, and Xamhain was
// written with half-open intervals in mind; and (2) the relevant
// header files are written in Objective-C.

// Generate a random float from [min, max).
inline float
randomFloat(const float min = 0.0f, const float max = 1.0f)
{
    return min + (max - min) * ((float)random() / ((float)RAND_MAX + 1.0));
}

// Generate a random double from [min, max).
inline double
randomDouble(const double min = 0.0, const double max = 1.0)
{
    return min + (max - min) * ((double)random() / ((double)RAND_MAX + 1.0));
}

// Generate a random integer.
inline int
randomInteger(const int max)
{
    return (int)(randomDouble() * max);
}

#endif // RANDOMNUMBERS_H
