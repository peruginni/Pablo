/* 
 * File:   VectorObject.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 15, 2010, 6:22 PM
 */

#ifndef _VECTORENTITY_H
#define	_VECTORENTITY_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QPoint>

#include "Stroke.h"
#include "Background.h"

class VectorEntity : public QObject
{
    Q_OBJECT

public:

    enum VectorEntityType {
        GENERAL, CIRCLE, RECTANGLE, PATH
    };

    VectorEntity(QObject *parent = 0);

    QString getName() const;
    void setName(const QString &);
    
    const QList<QPoint>* getControlPoints() const;

    void edit(int i, const QPoint &_edited);

    Stroke getStroke() const;
    void setStroke(const Stroke &);
    Background getBackground() const;
    void setBackgroundColor(int r, int g, int b, int a = 255);
    VectorEntityType getType() const;
    void setType(const VectorEntityType);
    
signals:
    void updated();

protected:
    QList<QPoint> controlPoints;
    QString name;
    Stroke stroke;
    Background background;
    VectorEntityType type;
};

#endif	/* _VECTORENTITY_H */

