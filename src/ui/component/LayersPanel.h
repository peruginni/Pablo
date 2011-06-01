/* 
 * File:   LayersPanel.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 17, 2010, 7:57 PM
 */

#ifndef _LAYERSPANEL_H
#define _LAYERSPANEL_H

#include <QtCore/QList>
#include <QtGui/QDockWidget>
#include <QtGui/QListWidgetItem>

#include "ui_LayersPanel.h"
#include "business/entity/VectorEntity.h"
#include "business/entity/Layer.h"
#include "business/controller/LayerController.h"

class QWidget;


class LayersPanel : public QDockWidget, public Ui::LayersPanel
{
    Q_OBJECT

public:
    LayersPanel(QWidget *parent = 0);
    
    void setLayerController(LayerController *);
    
public slots:
    void layerUp();
    void layerDown();
    void layerAdd();
    void layerRemove();
    void layerSelect(QListWidgetItem *);
    void updateView();
    
private:
    LayerController *layerController;
    
};

#endif	/* _LAYERSPANEL_H */

