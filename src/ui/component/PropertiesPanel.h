/* 
 * File:   PropertiesPanel.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 17, 2010, 7:58 PM
 */

#ifndef _PROPERTIESPANEL_H
#define	_PROPERTIESPANEL_H

#include <QtGui/QDockWidget>

#include "ui_PropertiesPanel.h"
#include "business/entity/Stroke.h"
#include "business/entity/Background.h"
#include "business/controller/PropertiesController.h"

class QWidget;

class PropertiesPanel : public QDockWidget, public Ui::PropertiesPanel
{
    Q_OBJECT

public:
    PropertiesPanel(QWidget *parent = 0);

    void setPropertiesController(PropertiesController *);

public slots:
    void updateView(const Stroke *, const Background *);

protected slots:
    void strokeSizeChanged(int);
    void strokeTypeSelected(int);
    void chooseStrokeColor();
    void chooseBackgroundColor();
    
private:
    PropertiesController *propertiesController;
            
};

#endif	/* _PROPERTIESPANEL_H */

