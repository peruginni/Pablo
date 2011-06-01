
#include "ToolController.h"

#include <QtCore/QLine>
#include <QtCore/QDebug>

/**
 * -------------------------------------------------------------
 *  constructors
 * -------------------------------------------------------------
 */

ToolController::ToolController(QObject *parent) : QObject(parent)
{
    layerController = 0;
    currentVectorEntity = 0;
    currentVectorEntityPointIndex = -1;
}


/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

void ToolController::setLayerController(LayerController *_layerController)
{
    layerController = _layerController;
}

ToolController::ToolState ToolController::getCurrentState() const
{
    return currentState;
}

void ToolController::setCurrentState(ToolState _state)
{
    currentState = _state;
}


/**
 * -------------------------------------------------------------
 *  core - delegated events
 * -------------------------------------------------------------
 */

void ToolController::mousePressEvent(QMouseEvent *e)
{
    QList<Layer*>* layers = layerController->getLayers();
    for(int i = 0; i < layers->size(); i++) {
        Layer* layer = layers->at(i);
        if(!layer->isEmpty()) {
            VectorEntity* vectorEntity = layer->get();
            const QList<QPoint>* points = vectorEntity->getControlPoints();
            for(int r = 0; r < points->size(); r++) {
                qreal d = QLineF(e->pos(), points->at(r)).length();
                if(d < 11) {
                    currentVectorEntity = vectorEntity;
                    currentVectorEntityPointIndex = r;
                    break;
                }
            }
        }
    }

}

void ToolController::mouseMoveEvent(QMouseEvent *e)
{
    if(currentVectorEntity != 0 && currentVectorEntityPointIndex != -1) {
        currentVectorEntity->edit(currentVectorEntityPointIndex, e->pos());
    }
}

void ToolController::mouseReleaseEvent(QMouseEvent *)
{
    currentVectorEntity = 0;
    currentVectorEntityPointIndex = -1;
}


