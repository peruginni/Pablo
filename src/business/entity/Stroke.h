/* 
 * File:   Stroke.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 18, 2010, 10:28 PM
 */

#ifndef _STROKE_H
#define	_STROKE_H

#include <QtGui/QColor>

class Stroke
{
public:
    Stroke();

    enum StrokeType {
        SOLID, DASHED, DOTTED
    };

    int getSize() const;
    void setSize(const int &);
    StrokeType getType() const;
    void setType(const StrokeType);
    const QColor* getColor() const;
    void setColor(const QColor &);

private:
    int size;
    StrokeType type;
    QColor color;

};

#endif	/* _STROKE_H */

