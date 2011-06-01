
#include "Rectangle.h"

/**
 * -------------------------------------------------------------
 *  constructors
 * -------------------------------------------------------------
 */

Rectangle::Rectangle(const QPoint &_a, const QPoint &_b)
{
    type = RECTANGLE;
    name = QString("rectangle");
    controlPoints.insert(0, _a);
    controlPoints.insert(1, _b);
}

/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

const QPoint* Rectangle::getPointA() const
{
    return &controlPoints.at(0);
}

void Rectangle::setPointA(const QPoint& _a)
{
    controlPoints.insert(0, _a);
}

const QPoint* Rectangle::getPointB() const
{
    return &controlPoints.at(1);
}

void Rectangle::setPointB(const QPoint& _b)
{
    controlPoints.insert(1, _b);
}
