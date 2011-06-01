/* 
 * File:   Circle.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 15, 2010, 6:41 PM
 */

#ifndef _CIRCLE_H
#define	_CIRCLE_H

#include "VectorEntity.h"

class Circle : public VectorEntity
{
public:
    Circle(const QPoint &_center, const QPoint &_border);
    
    const QPoint* getPointCenter() const;
    void setPointCenter(const QPoint&);
    const QPoint* getPointBorder() const;
    void setPointBorder(const QPoint&);
};


#endif	/* _CIRCLE_H */

