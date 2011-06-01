/* 
 * File:   ToolController.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 30, 2010, 9:20 PM
 */

#ifndef _TOOLCONTROLLER_H
#define	_TOOLCONTROLLER_H

#include <QtCore/QObject>
#include <QtGui/QMouseEvent>

#include "business/controller/LayerController.h"

class ToolController : public QObject
{
    Q_OBJECT

public:

    enum ToolState
    {
        SELECT, MOVE, RECTANGLE, CIRCLE, PATH
    };

    ToolController(QObject *parent = 0);
    
    void setLayerController(LayerController *);

    ToolState getCurrentState() const;
    void setCurrentState(ToolState);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);


private:
    ToolState currentState;
    LayerController *layerController;
    VectorEntity *currentVectorEntity;
    int currentVectorEntityPointIndex;

};

#endif	/* _TOOLCONTROLLER_H */

