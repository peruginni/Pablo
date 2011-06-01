
#include "MainWindow.h"

#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QToolBar>
#include <QtGui/QStatusBar>
#include <QtGui/QMessageBox>
#include <QtCore/QPoint>

#include "business/entity/Rectangle.h"
#include "business/entity/Circle.h"
#include "business/entity/Path.h"

/**
 * -------------------------------------------------------------
 *  constructors
 * -------------------------------------------------------------
 */

MainWindow::MainWindow()
{
    layerController = 0;
    propertiesController = 0;
    toolController = 0;

    initBusiness();

    createActions();
    createMainMenu();
    createToolBar();
    createStatusBar();
    createCanvas();
    createPropertiesPanel();
    createLayersPanel();

    setWindowIcon(QIcon(":/icons/pablo"));
    setMinimumSize(800, 600);

    show();
}

/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

PropertiesPanel* MainWindow::getPropertiesPanel() const
{
    return propertiesPanel;
}

LayersPanel* MainWindow::getLayersPanel() const
{
    return layersPanel;
}

Canvas* MainWindow::getCanvas() const
{
    return canvas;
}

/**
 * -------------------------------------------------------------
 *  core - initialization
 * -------------------------------------------------------------
 */

void MainWindow::initBusiness()
{
    layerController = new LayerController(this);
    propertiesController = new PropertiesController(this);
    propertiesController->setLayerController(layerController);
    toolController = new ToolController(this);
    toolController->setLayerController(layerController);
    
    connect(layerController, SIGNAL(layerSelected(Layer *)),
            propertiesController, SLOT(initializeFromLayer(Layer *)));
}

void MainWindow::createActions()
{
    actionCanvasNew = new QAction(tr("New"), this);
    actionCanvasNew->setIcon(QIcon(":/icons/canvas"));
    actionCanvasNew->setIconVisibleInMenu(true);
    connect(actionCanvasNew, SIGNAL(triggered()),
            this, SLOT(canvasNew()));

    actionQuit = new QAction(tr("Quit"), this);
    actionQuit->setIcon(QIcon(":/icons/quit"));
    actionQuit->setIconVisibleInMenu(true);
    connect(actionQuit, SIGNAL(triggered()),
            this, SLOT(close())); // close() is defined in QWidget

    actionToolSelect = new QAction(tr("Select"), this);
    actionToolSelect->setIcon(QIcon(":/icons/toolSelect"));
    actionToolSelect->setIconVisibleInMenu(true);
    connect(actionToolSelect, SIGNAL(triggered()),
            this, SLOT(toolSelect()));

    actionToolMove = new QAction(tr("Move"), this);
    actionToolMove->setIcon(QIcon(":/icons/toolMove"));
    actionToolMove->setIconVisibleInMenu(true);
    connect(actionToolMove, SIGNAL(triggered()),
            this, SLOT(toolMove()));

    actionToolRectangle = new QAction(tr("Rectangle"), this);
    actionToolRectangle->setIcon(QIcon(":/icons/toolRectangle"));
    actionToolRectangle->setIconVisibleInMenu(true);
    connect(actionToolRectangle, SIGNAL(triggered()),
            this, SLOT(toolRectangle()));

    actionToolCircle = new QAction(tr("Circle"), this);
    actionToolCircle->setIcon(QIcon(":/icons/toolCircle"));
    actionToolCircle->setIconVisibleInMenu(true);
    connect(actionToolCircle, SIGNAL(triggered()),
            this, SLOT(toolCircle()));

    actionToolPath = new QAction(tr("Path"), this);
    actionToolPath->setIcon(QIcon(":/icons/toolPath"));
    actionToolPath->setIconVisibleInMenu(true);
    connect(actionToolPath, SIGNAL(triggered()),
            this, SLOT(toolPath()));

    actionViewLayers = new QAction(tr("Layers"), this);
    actionViewLayers->setCheckable(true);
    actionViewLayers->setChecked(true);
    actionViewLayers->setIcon(QIcon(":/icons/layers"));
    actionViewLayers->setIconVisibleInMenu(true);
    connect(actionViewLayers, SIGNAL(toggled(bool)),
            this, SLOT(viewLayers(bool)));

    actionViewProperties = new QAction(tr("Properties"), this);
    actionViewProperties->setCheckable(true);
    actionViewProperties->setChecked(true);
    actionViewProperties->setIcon(QIcon(":/icons/properties"));
    actionViewProperties->setIconVisibleInMenu(true);
    connect(actionViewProperties, SIGNAL(toggled(bool)),
            this, SLOT(viewProperties(bool)));

    actionHelpAbout = new QAction(tr("About"), this);
    actionHelpAbout->setIcon(QIcon(":/icons/info"));
    actionHelpAbout->setIconVisibleInMenu(true);
    connect(actionHelpAbout, SIGNAL(triggered()),
            this, SLOT(helpAbout()));

}

void MainWindow::createMainMenu()
{
    mainMenuCanvas = menuBar()->addMenu(tr("Canvas"));
    mainMenuCanvas->addAction(actionCanvasNew);
    mainMenuCanvas->addSeparator();
    mainMenuCanvas->addAction(actionQuit);

    mainMenuTools = menuBar()->addMenu(tr("Tools"));
    //mainMenuTools->addAction(actionToolSelect);
    //mainMenuTools->addAction(actionToolMove);
    //mainMenuTools->addSeparator();
    mainMenuTools->addAction(actionToolRectangle);
    mainMenuTools->addAction(actionToolCircle);
    mainMenuTools->addAction(actionToolPath);

    mainMenuView = menuBar()->addMenu(tr("View"));
    mainMenuView->addAction(actionViewProperties);
    mainMenuView->addAction(actionViewLayers);

    mainMenuHelp = menuBar()->addMenu(tr("Help"));
    mainMenuHelp->addAction(actionHelpAbout);
}

void MainWindow::createToolBar()
{
    toolbarCanvas = addToolBar(tr("Canvas"));
    toolbarCanvas->addAction(actionCanvasNew);
    toolbarCanvas->setFixedHeight(50);

    toolbarTools = addToolBar(tr("Tools"));
    //toolbarTools->addAction(actionToolSelect);
    //toolbarTools->addAction(actionToolMove);
    //toolbarTools->addSeparator();
    toolbarTools->addAction(actionToolRectangle);
    toolbarTools->addAction(actionToolCircle);
    toolbarTools->addAction(actionToolPath);
}

void MainWindow::createStatusBar()
{
     sendMessageToStatusBar(tr("Welcome to Pablo!"));
}

void MainWindow::createCanvas()
{
    canvas = new Canvas(this);
    canvas->setLayerController(layerController);
    canvas->setToolController(toolController);
    connect(layerController, SIGNAL(updated()),
            canvas, SLOT(updateView()));
    connect(propertiesController, SIGNAL(updated()),
            canvas, SLOT(updateView()));
    setCentralWidget(canvas);
}

void MainWindow::createPropertiesPanel()
{
    propertiesPanel = new PropertiesPanel(this);
    propertiesPanel->setPropertiesController(propertiesController);
    addDockWidget(Qt::RightDockWidgetArea, propertiesPanel);
}

void MainWindow::createLayersPanel()
{
    layersPanel = new LayersPanel(this);
    layersPanel->setLayerController(layerController);
    addDockWidget(Qt::RightDockWidgetArea, layersPanel);
}


/**
 * -------------------------------------------------------------
 *  core - slots
 * -------------------------------------------------------------
 */

void MainWindow::canvasNew()
{
    if(layerController != 0) {
        layerController->clear();
    }
    canvas->updateView();
}

void MainWindow::toolSelect()
{
    toolController->setCurrentState(ToolController::SELECT);
}

void MainWindow::toolMove()
{
    toolController->setCurrentState(ToolController::MOVE);
}

void MainWindow::toolRectangle()
{
    if(layerController != 0) {
        if(layerController->isEmpty()) {
            layerController->layerAdd();
        }
        Layer *layer = layerController->getCurrentLayer();
        if(layer != 0) {
            Rectangle *rec = new Rectangle(
                    QPoint(100,100),
                    QPoint(150,150)
            );
            layer->add(rec);
        }
    }
}

void MainWindow::toolCircle()
{
    if(layerController != 0) {
        if(layerController->isEmpty()) {
            layerController->layerAdd();
        }
        Layer *layer = layerController->getCurrentLayer();
        if(layer != 0) {
            Circle *circle = new Circle(
                    QPoint(300,100),
                    QPoint(350,150)
            );
            layer->add(circle);
        }
    }
}

void MainWindow::toolPath()
{
    if(layerController != 0) {
        if(layerController->isEmpty()) {
            layerController->layerAdd();
        }
        Layer *layer = layerController->getCurrentLayer();
        if(layer != 0) {
            Path *path = new Path();
            path->add(QPoint(200,300));
            path->add(QPoint(240,340));
            path->add(QPoint(280,330));
            path->add(QPoint(340,390));
            path->add(QPoint(440,310));
            layer->add(path);
        }
    }
}

void MainWindow::viewLayers(bool status)
{
    layersPanel->setEnabled(status);
}

void MainWindow::viewProperties(bool status)
{
    propertiesPanel->setEnabled(status);
}

void MainWindow::helpAbout()
{
    QMessageBox::about(this, tr("About Pablo"),
        tr("<h1>Pablo 1.0</h1>"
           "<p>Copyright &copy; 2010 Ondra Macoszek</p>"
           "<p>Icons by <a href=\"http://www.mattballdesign.com\">Matt Ball</a></p>"
           "<p>Incredibly awesome vector editor that cannot save image.</p>"));

}

void MainWindow::sendMessageToStatusBar(QString message)
{
    statusBar()->showMessage(message);
}


