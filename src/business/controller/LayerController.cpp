
#include "LayerController.h"

int LayerController::counter = 0;


/**
 * -------------------------------------------------------------
 *  constructors, destructor
 * -------------------------------------------------------------
 */

LayerController::LayerController(QObject *parent) : QObject(parent)
{
    invalidateCurrentLayerIndex();
    layers = new QList<Layer*>;
}

LayerController::~LayerController()
{
    for (int i = 0; i < layers->size(); i++) {
        Layer *layer = layers->at(i);
        delete layer;
    }
    delete layers;
}

/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

QList<Layer*>* LayerController::getLayers() const
{
    return layers;
}

Layer* LayerController::getCurrentLayer()
{
    if(isValidCurrentLayerIndex()) {
        return layers->value(getCurrentLayerIndex());
    }
    return 0;
}

Layer* LayerController::getLayerAt(int index) const
{
    if(isValidCurrentLayerIndex(index)) {
        return layers->value(index);
    }
    return 0;
}

int LayerController::getCurrentLayerIndex() const
{
    return currentLayerIndex;
}

void LayerController::setCurrentLayerIndex(int index)
{
    currentLayerIndex = index;
}

bool LayerController::isValidCurrentLayerIndex() const
{
    if(currentLayerIndex == -1) {
        return false;
    }
    return isValidCurrentLayerIndex(currentLayerIndex);
}

bool LayerController::isValidCurrentLayerIndex(int index) const
{
    int layersSize = layers->size();
    if(layersSize == 0) {
        return false;
    } else if(index < 0 || index >= layersSize) {
        return false;
    } else {
        return true;
    }
}

void LayerController::invalidateCurrentLayerIndex()
{
    currentLayerIndex = -1;
}

bool LayerController::isEmpty() const
{
    return layers->isEmpty();
}

void LayerController::clear()
{
    layers->clear();
    emit updated();
}

/**
 * -------------------------------------------------------------
 *  core - slots
 * -------------------------------------------------------------
 */

void LayerController::layerUp()
{
    if(isValidCurrentLayerIndex()) {
        if(currentLayerIndex > 0) {
            int upperIndex = currentLayerIndex - 1;
            layers->swap(currentLayerIndex, upperIndex);
            currentLayerIndex = upperIndex;
            emit updated();
        }
    }
}

void LayerController::layerDown()
{
    if(isValidCurrentLayerIndex()) {
        int lastIndex = layers->size() - 1;
        if(currentLayerIndex < lastIndex) {
            int lowerIndex = currentLayerIndex + 1;
            layers->swap(currentLayerIndex, lowerIndex);
            currentLayerIndex = lowerIndex;
            emit updated();
        }
    }
}

void LayerController::layerAdd()
{
    Layer *newLayer = new Layer(this);
    newLayer->setName(QString("empty layer %1").arg(LayerController::counter++));
    connect(newLayer, SIGNAL(updated()),
            this, SLOT(layerUpdated()));

    layers->prepend(newLayer);
    layerSelect(0);
    emit updated();
}

void LayerController::layerRemove()
{
    if(isValidCurrentLayerIndex()) {
        Layer *deletedLayer = layers->at(currentLayerIndex);
        layers->removeAt(currentLayerIndex);
        delete deletedLayer;

        // set new position of current layer index
        if(--currentLayerIndex < 0) {
            currentLayerIndex = 0;
        } 

        if(!isValidCurrentLayerIndex()) {
            invalidateCurrentLayerIndex();
        }

        emit updated();
    }
}

void LayerController::layerSelect(int index)
{
    if(isValidCurrentLayerIndex(index)) {
        currentLayerIndex = index;
        emit layerSelected(getCurrentLayer());
    }
}

void LayerController::layerUpdated()
{
    int i = getCurrentLayerIndex();
    layerSelect(i);
    emit updated();
}