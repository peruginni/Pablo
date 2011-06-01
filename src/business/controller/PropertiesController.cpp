
#include <QDebug>
#include "PropertiesController.h"
#include "LayerController.h"


/**
 * -------------------------------------------------------------
 *  constructors, destructor
 * -------------------------------------------------------------
 */

PropertiesController::PropertiesController(QObject* parent) : QObject(parent)
{
    layerController = 0;
}

/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

void PropertiesController::setLayerController(LayerController *_layerController)
{
    layerController = _layerController;
}

const Stroke* PropertiesController::getCurrentStroke() const
{
    return &currentStroke;
}

void PropertiesController::setCurrentStroke(const Stroke &_stroke)
{
    currentStroke = _stroke;
}

const Background* PropertiesController::getCurrentBackground() const
{
    return &currentBackground;
}

void PropertiesController::setCurrentBackground(const Background &_background)
{
    currentBackground = _background;
}


void PropertiesController::setStrokeSize(int _size)
{
    currentStroke.setSize(_size);
    updateCurrentLayer();
}

void PropertiesController::setStrokeType(Stroke::StrokeType _type)
{
    currentStroke.setType(_type);
    updateCurrentLayer();
}

void PropertiesController::setStrokeColor(const QColor &_color)
{
    currentStroke.setColor(_color);
    updateCurrentLayer();
}

void PropertiesController::setBackgroundColor(const QColor &_color)
{
    currentBackground.setColor(_color);
    updateCurrentLayer();
}

void PropertiesController::updateCurrentLayer()
{
    Layer *currentLayer = layerController->getCurrentLayer();
    if(currentLayer != 0) {
        if(!currentLayer->isEmpty()) {
            QColor c = currentBackground.getColor();
            VectorEntity *e = currentLayer->get();
            e->setStroke(currentStroke);
            e->setBackgroundColor(
                c.red(), c.green(), c.blue()
            );
        }
    }
}


/**
 * -------------------------------------------------------------
 *  core - slots
 * -------------------------------------------------------------
 */

void PropertiesController::initializeFromLayer(Layer * layer)
{
    if(layer != 0) {
        if(!layer->isEmpty()) {
            currentStroke = layer->get()->getStroke();
            currentBackground = layer->get()->getBackground();
            emit propertiesInitialized(&currentStroke, &currentBackground);
        }
    }
}

