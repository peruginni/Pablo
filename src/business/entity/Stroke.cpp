
#include "Stroke.h"

/**
 * -------------------------------------------------------------
 *  constructors
 * -------------------------------------------------------------
 */

Stroke::Stroke()
{
    size = 1;
    type = SOLID;
    color = Qt::black;
}


/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

int Stroke::getSize() const
{
    return size;
}

void Stroke::setSize(const int &_size)
{
    size = _size;
}

Stroke::StrokeType Stroke::getType() const
{
    return type;
}

void Stroke::setType(const StrokeType _type)
{
    type = _type;
}

const QColor* Stroke::getColor() const
{
    return &color;
}

void Stroke::setColor(const QColor &_color)
{
    color = _color;
}
