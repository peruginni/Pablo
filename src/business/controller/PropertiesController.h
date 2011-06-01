/* 
 * File:   PropertiesController.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 22, 2010, 1:08 PM
 */

#ifndef _PROPERTIESCONTROLLER_H
#define	_PROPERTIESCONTROLLER_H

#include <QtCore/QObject>
#include <QtGui/QColor>

#include "business/entity/Stroke.h"
#include "business/entity/Background.h"
#include "business/entity/Layer.h"
#include "business/controller/LayerController.h"


class PropertiesController : public QObject
{
    Q_OBJECT

public:
    PropertiesController(QObject *parent = 0);

    void setLayerController(LayerController *_layerController);

    const Stroke* getCurrentStroke() const;
    void setCurrentStroke(const Stroke &);
    const Background* getCurrentBackground() const;
    void setCurrentBackground(const Background &);

    void setStrokeSize(int);
    void setStrokeType(Stroke::StrokeType);
    void setStrokeColor(const QColor &);
    void setBackgroundColor(const QColor &);
    void updateCurrentLayer();

public slots:
    void initializeFromLayer(Layer *);
    
signals:
    void propertiesInitialized(const Stroke *, const Background *);
    void updated();

private:
    Stroke currentStroke;
    Background currentBackground;

    LayerController* layerController;

};

#endif	/* _PROPERTIESCONTROLLER_H */

