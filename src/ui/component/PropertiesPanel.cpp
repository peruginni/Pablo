
#include "PropertiesPanel.h"

#include <QDebug>
#include <QtGui/QComboBox>
#include <QtGui/QColorDialog>


/**
 * -------------------------------------------------------------
 *  constructors, destructor
 * -------------------------------------------------------------
 */

PropertiesPanel::PropertiesPanel(QWidget* parent) : QDockWidget(parent)
{
    propertiesController = 0;
    
    setupUi(this);
}
/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

void PropertiesPanel::setPropertiesController(PropertiesController *_propertiesController)
{
    propertiesController = _propertiesController;

    connect(propertiesController, SIGNAL(propertiesInitialized(const Stroke *, const Background *)),
            this, SLOT(updateView(const Stroke *, const Background *)));

    updateView(propertiesController->getCurrentStroke(), propertiesController->getCurrentBackground());
}

/**
 * -------------------------------------------------------------
 *  core - slots
 * -------------------------------------------------------------
 */

void PropertiesPanel::strokeSizeChanged(int _size)
{
    if(propertiesController != 0) {
        propertiesController->setStrokeSize(_size);
    }
}

void PropertiesPanel::strokeTypeSelected(int _type)
{
    if(propertiesController != 0) {
        Stroke::StrokeType type;
        switch(_type) {
            case 1: type = Stroke::DASHED; break;
            case 2: type = Stroke::DOTTED; break;
            default: type = Stroke::SOLID;
        }
        propertiesController->setStrokeType(type);
    }
}

void PropertiesPanel::chooseStrokeColor()
{
    if(propertiesController != 0) {
        QColor color = QColorDialog::getColor(*(propertiesController->getCurrentStroke()->getColor()));
        if (color.isValid()) {
            propertiesController->setStrokeColor(color);
        }
    }
}

void PropertiesPanel::chooseBackgroundColor()
{
    if(propertiesController != 0) {
        QColor color = QColorDialog::getColor(propertiesController->getCurrentBackground()->getColor());
        if (color.isValid()) {
            propertiesController->setBackgroundColor(color);
        }
    }
}

void PropertiesPanel::updateView(const Stroke * stroke, const Background * background)
{
    if(stroke != 0 && background != 0) {
        strokeSizeSlider->setValue(stroke->getSize());

        int typeIndex = 0;
        switch(stroke->getType()) {
            case Stroke::SOLID: typeIndex = 0; break;
            case Stroke::DASHED: typeIndex = 1; break;
            case Stroke::DOTTED: typeIndex = 2; break;
        }
        
        strokeTypeComboBox->setCurrentIndex(typeIndex);
    }
}

