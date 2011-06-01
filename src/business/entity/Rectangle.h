/* 
 * File:   Rectangle.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 15, 2010, 6:37 PM
 */

#ifndef _RECTANGLE_H
#define	_RECTANGLE_H

#include "VectorEntity.h"

class Rectangle : public VectorEntity
{
public:
    Rectangle(const QPoint &a, const QPoint &b);

    const QPoint* getPointA() const;
    void setPointA(const QPoint&);
    const QPoint* getPointB() const;
    void setPointB(const QPoint&);
    
};

#endif	/* _RECTANGLE_H */

