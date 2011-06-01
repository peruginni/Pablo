/* 
 * File:   Background.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 18, 2010, 10:28 PM
 */

#ifndef _BACKGROUND_H
#define	_BACKGROUND_H

#include <QtGui/QColor>

class Background 
{
public:
    Background();

    QColor getColor() const;
    void setColor(const QColor &);

private:
    QColor color;
    
};


#endif	/* _BACKGROUND_H */

