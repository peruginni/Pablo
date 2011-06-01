
#include "LayersPanel.h"
#include "business/controller/LayerController.h"

/**
 * -------------------------------------------------------------
 *  constructors, destructor
 * -------------------------------------------------------------
 */

LayersPanel::LayersPanel(QWidget* parent) : QDockWidget(parent)
{
    layerController = 0;
    
    setupUi(this);
}


/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

void LayersPanel::setLayerController(LayerController *lc)
{
    layerController = lc;
    
    connect(layerController, SIGNAL(updated()),
            this, SLOT(updateView()));

    updateView();
}


/**
 * -------------------------------------------------------------
 *  core - slots
 * -------------------------------------------------------------
 */

void LayersPanel::layerUp()
{
    if(layerController != 0) {
        layerController->layerUp();
    }
}

void LayersPanel::layerDown()
{
    if(layerController != 0) {
        layerController->layerDown();
    }
}

void LayersPanel::layerAdd()
{
    if(layerController != 0) {
        layerController->layerAdd();
    }
}

void LayersPanel::layerRemove()
{
    if(layerController != 0) {
        layerController->layerRemove();
    }
}

void LayersPanel::layerSelect(QListWidgetItem* item)
{
    if(layerController != 0) {
        int id = item->data(Qt::UserRole).toInt();
        layerController->layerSelect(id);
    }
}

void LayersPanel::updateView()
{
    if(layerController != 0) {
        layersList->clear();

        const QList<Layer*>* layers = layerController->getLayers();

        for(int i = 0; i < layers->size(); i++) {
            QListWidgetItem *item = new QListWidgetItem(layers->at(i)->getName(), layersList);
            item->setData(Qt::UserRole, i);
        }

        if(layerController->isValidCurrentLayerIndex()) {
            layersList->setCurrentRow(layerController->getCurrentLayerIndex());
        }
    }
}

