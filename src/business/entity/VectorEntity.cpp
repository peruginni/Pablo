
#include "VectorEntity.h"

#include <QtCore/QString>
#include <QtCore/QPoint>
#include <QtDebug>

#include "Stroke.h"
#include "Background.h"

/**
 * -------------------------------------------------------------
 *  constructors
 * -------------------------------------------------------------
 */

VectorEntity::VectorEntity(QObject *parent) : QObject(parent)
{
    type = GENERAL;
    name = QString("vector entity");
}

/**
 * -------------------------------------------------------------
 *  core - getter,setter
 * -------------------------------------------------------------
 */


void VectorEntity::edit(int index, const QPoint &_edited)
{
    if(index >= 0 && index < controlPoints.size()) {
        controlPoints.replace(index, _edited);
    }
    emit updated();
}

QString VectorEntity::getName() const
{
    return name;
}

void VectorEntity::setName(const QString &_name)
{
    name = _name;
    emit updated();
}

const QList<QPoint>* VectorEntity::getControlPoints() const
{
    return &controlPoints;
}

Stroke VectorEntity::getStroke() const
{
    return stroke;
}

void VectorEntity::setStroke(const Stroke &_stroke)
{
    stroke = _stroke;
    emit updated();
}

Background VectorEntity::getBackground() const
{
    return background;
}

void VectorEntity::setBackgroundColor(int r, int g, int b, int a)
{
    QColor c(r, g, b, a);
    background.setColor(c);
    emit updated();
}

VectorEntity::VectorEntityType VectorEntity::getType() const
{
    return type;
}

void VectorEntity::setType(const VectorEntityType _type)
{
    type = _type;
}
