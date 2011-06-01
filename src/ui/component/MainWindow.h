/* 
 * File:   MainWindow.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 17, 2010, 3:16 PM
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "business/controller/LayerController.h"
#include "business/controller/PropertiesController.h"
#include "business/controller/ToolController.h"

#include "Canvas.h"
#include "PropertiesPanel.h"
#include "LayersPanel.h"

class QAction;


class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
    MainWindow();

    PropertiesPanel* getPropertiesPanel() const;
    LayersPanel* getLayersPanel() const;
    Canvas* getCanvas() const;

protected:
    // redefined close event
    //void closeEvent(QCloseEvent *event);

private slots:
    // slots for main menubar actions
    void canvasNew();
    void toolSelect();
    void toolMove();
    void toolRectangle();
    void toolCircle();
    void toolPath();
    void viewLayers(bool);
    void viewProperties(bool);
    void helpAbout();
    
    // other slots
    void sendMessageToStatusBar(QString);


private:
    // business initialization
    void initBusiness();

    // gui initialization
    void createActions();
    void createMainMenu();
    void createToolBar();
    void createStatusBar();
    void createCanvas();
    void createPropertiesPanel();
    void createLayersPanel();

    // gui helpers
    bool confirmToContinue();

    // gui component instances
    PropertiesPanel *propertiesPanel;
    LayersPanel *layersPanel;
    Canvas *canvas;

    // action instances
    QAction *actionCanvasNew;
    QAction *actionQuit;
    QAction *actionToolSelect;
    QAction *actionToolMove;
    QAction *actionToolRectangle;
    QAction *actionToolCircle;
    QAction *actionToolPath;
    QAction *actionViewLayers;
    QAction *actionViewProperties;
    QAction *actionHelpAbout;

    // main menu bar instances
    QMenu *mainMenuCanvas;
    QMenu *mainMenuTools;
    QMenu *mainMenuView;
    QMenu *mainMenuHelp;

    // toolbar instances
    QToolBar *toolbarCanvas;
    QToolBar *toolbarTools;

    // statusbar instances
    // none

    // business layer instances
    LayerController *layerController;
    PropertiesController *propertiesController;
    ToolController *toolController;

};

#endif	/* _MAINWINDOW_H */

