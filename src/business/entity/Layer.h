/* 
 * File:   Layer.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 18, 2010, 3:58 PM
 */

#ifndef _LAYER_H
#define	_LAYER_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include "VectorEntity.h"


class Layer : public QObject
{
    Q_OBJECT

public:
    Layer(QObject *parent = 0);
    ~Layer();
    

    void add(VectorEntity *);
    VectorEntity* get() const;
    bool isEmpty() const;

    QString getName() const;
    void setName(const QString &);

public slots:
    void update();

signals:
    void updated();

private:
    VectorEntity *vectorEntity;
    QString name;

};

#endif	/* _LAYER_H */

