
#include "Background.h"
#include <QtCore/QDebug>

/**
 * -------------------------------------------------------------
 *  constructors
 * -------------------------------------------------------------
 */

Background::Background()
{
    color = Qt::white;
}


/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

QColor Background::getColor() const
{
    return color;
}

void Background::setColor(const QColor &_color)
{
    color = _color;
}




