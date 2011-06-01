/* 
 * File:   Canvas.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 17, 2010, 7:55 PM
 */

#ifndef _CANVAS_H
#define	_CANVAS_H

#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>
#include <QtCore/QSize>
#include <QtCore/QEvent>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtCore/QPoint>

#include "ui_Canvas.h"

#include "business/controller/LayerController.h"
#include "business/controller/ToolController.h"
#include "business/entity/Rectangle.h"
#include "business/entity/Circle.h"
#include "business/entity/Path.h"
#include "business/entity/VectorEntity.h"



class Canvas : public QWidget 
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = 0);
    
    void setLayerController(LayerController *);
    void setToolController(ToolController *);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void paintEvent(QPaintEvent *);
    void paintVectorEntity(const Rectangle *, QPainter *);
    void paintVectorEntity(const Circle *, QPainter *);
    void paintVectorEntity(const Path *, QPainter *);
    void paintControlPoints(const VectorEntity *, QPainter *);
    QPen getPen(const Stroke &);
    QBrush getBrush(const Background &);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    
public slots:
    void updateView();

signals:
    void clicked();

private:
    LayerController *layerController;
    ToolController *toolController;
    QPoint mousePressPoint;
    bool isMouseDragging;
    Layer *selectedLayer;
    QPoint *selectedPoint;

    QBrush controlPointBrush;
    QPen controlPointPen;

};

#endif	/* _CANVAS_H */

