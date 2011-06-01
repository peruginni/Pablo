/*
 * File:   main.cpp
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 13, 2010, 6:52 PM
 */

#include <QtGui/QApplication>

#include "ui/component/MainWindow.h"
#include "ui/component/Canvas.h"

int main(int argc, char *argv[]) {
    // initialize resources by basename of file
    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    new MainWindow;
    
    return app.exec();
}
