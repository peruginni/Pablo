/* 
 * File:   Path.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 18, 2010, 10:36 PM
 */

#ifndef _PATH_H
#define	_PATH_H

#include "VectorEntity.h"

class Path : public VectorEntity
{
public:
    Path();

    void add(const QPoint &);
    void edit(const QPoint &original, const QPoint &edited);
};


#endif	/* _PATH_H */

