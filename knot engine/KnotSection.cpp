//  Description of knot strokes and sections.
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

#include "KnotSection.h"

#include <OpenGL/gl.h>

#include "Position.h"
#include "Stroke.h"
#include "StrokeSet.h"

namespace
{
    static const GLint t0[4] = {  1,  0,  0,  1 };
    static const GLint t1[4] = {  0, -1,  1,  0 };
    static const GLint t2[4] = { -1,  0,  0, -1 };
    static const GLint t3[4] = {  0,  1, -1,  0 };
    static const GLint t4[4] = { -1,  0,  0,  1 };
    static const GLint t5[4] = {  0, -1, -1,  0 };
    static const GLint t6[4] = {  1,  0,  0, -1 };
    static const GLint t7[4] = {  0,  1,  1,  0 };

    static const GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };

    void
    strokeCorners(
        const KnotSection &section,
        Position center, GLfloat size, GLfloat radius, GLfloat angle,
        const StrokeSet &strokes,
        const GLfloat ltCornerColor[4], const GLfloat rbCornerColor[4])
    {
        // Draw corners of the section if needed.
        if (section.leftTop() == D) {
            glColor4fv(ltCornerColor);
            strokes[StrokeSet::Corner].draw(center, size, radius, angle, t0);
        }
        if (section.rightBottom() == D) {
            glColor4fv(rbCornerColor);
            strokes[StrokeSet::Corner].draw(center, size, radius, angle, t2);
        }
    }

    void
    diagonalStroke(
        direction from, direction to, bool mirror,
        Position center, GLfloat size, GLfloat radius, GLfloat angle,
        const StrokeSet &strokes, const GLfloat color[4])
    {
        glColor4fv(color);

        switch (4*from + to) {

        case 4*D + D:
            strokes[StrokeSet::DDD].draw(center, size, radius, angle,
                                         mirror ? t4 : t0);
            break;

        case 4*D + H:
            strokes[StrokeSet::DHD].draw(center, size, radius, angle,
                                         mirror ? t6 : t2);
            break;

        case 4*D + V:
            strokes[StrokeSet::DHD].draw(center, size, radius, angle,
                                         mirror ? t1 : t7);
            break;

        case 4*H + D:
            strokes[StrokeSet::DHD].draw(center, size, radius, angle,
                                         mirror ? t4 : t0);
            break;

        case 4*H + H:
            strokes[StrokeSet::DHH].draw(center, size, radius, angle,
                                         mirror ? t4 : t0);
            break;

        case 4*H + V:
            strokes[StrokeSet::DHV].draw(center, size, radius, angle,
                                         mirror ? t4 : t0);
            break;

        case 4*V + D:
            strokes[StrokeSet::DHD].draw(center, size, radius, angle,
                                         mirror ? t3 : t5);
            break;

        case 4*V + H:
            strokes[StrokeSet::DHV].draw(center, size, radius, angle,
                                         mirror ? t6 : t2);
            break;

        case 4*V + V:
            strokes[StrokeSet::DHH].draw(center, size, radius, angle,
                                         mirror ? t1 : t5);
            break;

        default:
            // Just ignore illegal diagonal strokes.
            break;
        }
    }

    void
    diagonalSection(
        const KnotSection &section,
        Position center, GLfloat size, GLfloat radius, GLfloat angle,
        const StrokeSet &outlineStrokes, const StrokeSet &fillStrokes,
        bool hollow,
        const GLfloat topColor[4], const GLfloat botColor[4],
        const GLfloat ltCornerColor[4], const GLfloat rbCornerColor[4])
    {
        // Draw bottom stroke.
        diagonalStroke(section.rightTop(), section.leftBottom(), true,
                       center, size, radius, angle,
                       outlineStrokes, hollow ? botColor : black);
        diagonalStroke(section.rightTop(), section.leftBottom(), true,
                       center, size, radius, angle,
                       fillStrokes, hollow ? black : botColor);

        // Draw top stroke.
        diagonalStroke(section.leftTop(), section.rightBottom(), false,
                       center, size, radius, angle,
                       outlineStrokes, hollow ? topColor : black);
        diagonalStroke(section.leftTop(), section.rightBottom(), false,
                       center, size, radius, angle,
                       fillStrokes, hollow ? black : topColor);

        // Draw corners if needed.
        strokeCorners(section, center, size, radius, angle,
                      outlineStrokes,
                      hollow ? ltCornerColor : black,
                      hollow ? rbCornerColor : black);
        strokeCorners(section, center, size, radius, angle,
                      fillStrokes,
                      hollow ? black : ltCornerColor,
                      hollow ? black : rbCornerColor);
    }

    void
    horizontalStroke(
        direction from, direction to, bool mirror,
        Position center, GLfloat size, GLfloat radius, GLfloat angle,
        const StrokeSet &strokes, const GLfloat color[4])
    {
        glColor4fv(color);

        switch (4*from + to) {

        case 4*D + D:
            strokes[StrokeSet::HDD].draw(center, size, radius, angle,
                                         mirror ? t2 : t0);
            break;

        case 4*D + H:
            strokes[StrokeSet::HDH].draw(center, size, radius, angle,
                                         mirror ? t6 : t0);
            break;

        case 4*D + V:
            strokes[StrokeSet::HDV].draw(center, size, radius, angle,
                                         mirror ? t6 : t0);
            break;

        case 4*H + D:
            strokes[StrokeSet::HDH].draw(center, size, radius, angle,
                                         mirror ? t2 : t4);
            break;

        case 4*H + H:
            strokes[StrokeSet::HHH].draw(center, size, radius, angle,
                                         mirror ? t2 : t0);
            break;

        case 4*H + V:
            strokes[StrokeSet::HHV].draw(center, size, radius, angle,
                                         mirror ? t6 : t0);
            break;

        case 4*V + D:
            strokes[StrokeSet::HDV].draw(center, size, radius, angle,
                                         mirror ? t2 : t4);
            break;

        case 4*V + H:
            strokes[StrokeSet::HHV].draw(center, size, radius, angle,
                                         mirror ? t2 : t4);
            break;

        case 4*V + V:
            strokes[StrokeSet::HVV].draw(center, size, radius, angle,
                                         mirror ? t2 : t0);
            break;

        case 4*N + N:
            // Stroke omitted (edge section).
            break;

        default:
            // Just ignore illegal horizontal strokes.
            break;
        }
    }

    void
    horizontalSection(
        const KnotSection &section,
        Position center, GLfloat size, GLfloat radius, GLfloat angle,
        const StrokeSet &outlineStrokes, const StrokeSet &fillStrokes,
        bool hollow,
        const GLfloat topColor[4], const GLfloat botColor[4],
        const GLfloat ltCornerColor[4], const GLfloat rbCornerColor[4])
    {
        // Draw bottom stroke.
        horizontalStroke(section.leftBottom(), section.rightBottom(), true,
                         center, size, radius, angle,
                         outlineStrokes, hollow ? botColor : black);
        horizontalStroke(section.leftBottom(), section.rightBottom(), true,
                         center, size, radius, angle,
                         fillStrokes, hollow ? black : botColor);

        // Draw top stroke.
        horizontalStroke(section.leftTop(), section.rightTop(), false,
                         center, size, radius, angle,
                         outlineStrokes, hollow ? topColor : black);
        horizontalStroke(section.leftTop(), section.rightTop(), false,
                         center, size, radius, angle,
                         fillStrokes, hollow ? black : topColor);

        // Draw corners if needed.
        strokeCorners(section, center, size, radius, angle,
                      outlineStrokes,
                      hollow ? ltCornerColor : black,
                      hollow ? rbCornerColor : black);
        strokeCorners(section, center, size, radius, angle,
                      fillStrokes,
                      hollow ? black : ltCornerColor,
                      hollow ? black : rbCornerColor);
    }

    void
    verticalStroke(
        direction from, direction to, bool mirror,
        Position center, GLfloat size, GLfloat radius, GLfloat angle,
        const StrokeSet &strokes, const GLfloat color[4])
    {
        glColor4fv(color);

        switch (4*from + to) {

        case 4*D + D:
            strokes[StrokeSet::HDD].draw(center, size, radius, angle,
                                         mirror ? t3 : t1);
            break;

        case 4*D + H:
            strokes[StrokeSet::HDV].draw(center, size, radius, angle,
                                         mirror ? t3 : t5);
            break;

        case 4*D + V:
            strokes[StrokeSet::HDH].draw(center, size, radius, angle,
                                         mirror ? t3 : t5);
            break;

        case 4*H + D:
            strokes[StrokeSet::HDV].draw(center, size, radius, angle,
                                         mirror ? t7 : t1);
            break;

        case 4*H + H:
            strokes[StrokeSet::HVV].draw(center, size, radius, angle,
                                         mirror ? t3 : t1);
            break;

        case 4*H + V:
            strokes[StrokeSet::HHV].draw(center, size, radius, angle,
                                         mirror ? t7 : t1);
            break;

        case 4*V + D:
            strokes[StrokeSet::HDH].draw(center, size, radius, angle,
                                         mirror ? t7 : t1);
            break;

        case 4*V + H:
            strokes[StrokeSet::HHV].draw(center, size, radius, angle,
                                         mirror ? t3 : t5);
            break;

        case 4*V + V:
            strokes[StrokeSet::HHH].draw(center, size, radius, angle,
                                         mirror ? t3 : t1);
            break;

        case 4*N + N:
            // Stroke omitted (edge section).
            break;

        default:
            // Just ignore illegal vertical strokes.
            break;
        }
    }

    void
    verticalSection(
        const KnotSection &section,
        Position center, GLfloat size, GLfloat radius, GLfloat angle,
        const StrokeSet &outlineStrokes, const StrokeSet &fillStrokes,
        bool hollow,
        const GLfloat topColor[4], const GLfloat botColor[4],
        const GLfloat ltCornerColor[4], const GLfloat rbCornerColor[4])
    {
        // Draw right stroke.
        verticalStroke(section.rightTop(), section.rightBottom(), true,
                       center, size, radius, angle,
                       outlineStrokes, hollow ? botColor : black);
        verticalStroke(section.rightTop(), section.rightBottom(), true,
                       center, size, radius, angle,
                       fillStrokes, hollow ? black : botColor);

        // Draw left stroke.
        verticalStroke(section.leftTop(), section.leftBottom(), false,
                       center, size, radius, angle,
                       outlineStrokes, hollow ? topColor : black);
        verticalStroke(section.leftTop(), section.leftBottom(), false,
                       center, size, radius, angle,
                       fillStrokes, hollow ? black : topColor);

        // Draw corners if needed.
        strokeCorners(section, center, size, radius, angle,
                      outlineStrokes,
                      hollow ? ltCornerColor : black,
                      hollow ? rbCornerColor : black);
        strokeCorners(section, center, size, radius, angle,
                      fillStrokes,
                      hollow ? black : ltCornerColor,
                      hollow ? black : rbCornerColor);
    }
}

void
KnotSection::draw(
    Position center, GLfloat size, GLfloat radius, GLfloat angle,
    const StrokeSet &outlineStrokes, const StrokeSet &fillStrokes,
    bool hollow,
    const GLfloat topColor[4], const GLfloat botColor[4],
    const GLfloat ltCornerColor[4], const GLfloat rbCornerColor[4]) const
{
    switch (mType) {

    case D:
        diagonalSection(*this, center, size, radius, angle,
                        outlineStrokes, fillStrokes, hollow,
                        topColor, botColor, ltCornerColor, rbCornerColor);
        break;

    case H:
        horizontalSection(*this, center, size, radius, angle,
                          outlineStrokes, fillStrokes, hollow,
                          topColor, botColor, ltCornerColor, rbCornerColor);
        break;

    case V:
        verticalSection(*this, center, size, radius, angle,
                        outlineStrokes, fillStrokes, hollow,
                        topColor, botColor, ltCornerColor, rbCornerColor);
        break;

    default:
        // Just ignore illegal section types.
        break;
    }
}
