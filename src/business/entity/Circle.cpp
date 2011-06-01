
#include "Circle.h"

/**
 * -------------------------------------------------------------
 *  constructors
 * -------------------------------------------------------------
 */

Circle::Circle(const QPoint &_center, const QPoint &_border)
{
    type = CIRCLE;
    name = QString("circle");
    controlPoints.insert(0, _center);
    controlPoints.insert(1, _border);
}


/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

const QPoint* Circle::getPointCenter() const
{
    return &controlPoints.at(0);
}

void Circle::setPointCenter(const QPoint& _pointCenter)
{
    controlPoints.insert(0, _pointCenter);
}

const QPoint* Circle::getPointBorder() const
{
    return &controlPoints.at(1);
}

void Circle::setPointBorder(const QPoint& _pointBorder)
{
    controlPoints.insert(1, _pointBorder);
}

