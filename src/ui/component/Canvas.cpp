
#include "Canvas.h"

#include <QtCore/QDebug>
#include <QtGui/QToolButton>
#include <QtCore/QList>
#include <QtCore/QPoint>

#include "business/entity/Layer.h"
#include "business/entity/Stroke.h"



/**
 * -------------------------------------------------------------
 *  constructors, destructor
 * -------------------------------------------------------------
 */

Canvas::Canvas(QWidget* parent) : QWidget(parent)
{
    layerController = 0;
    toolController = 0;

    QColor brushColor = Qt::gray;
    brushColor.setAlpha(70);
    controlPointBrush = QBrush(brushColor, Qt::SolidPattern);
    QColor penColor = Qt::red;
    penColor.setAlpha(70);
    controlPointPen = QPen(penColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}


/**
 * -------------------------------------------------------------
 *  core - getters/setters
 * -------------------------------------------------------------
 */

void Canvas::setLayerController(LayerController *_layerController)
{
    layerController = _layerController;
}

void Canvas::setToolController(ToolController *_toolController)
{
    toolController = _toolController;
}


/**
 * -------------------------------------------------------------
 *  core - rendering
 * -------------------------------------------------------------
 */

QSize Canvas::minimumSizeHint() const
{
    return QSize(640, 480);
}

QSize Canvas::sizeHint() const
{
    return QSize(640, 480);
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(layerController != 0) {
        QList<Layer*> *layers = layerController->getLayers();

        for (int i = 0; i < layers->size(); i++) {
            Layer *layer = layers->at(i);
            if(layer != 0 && !layer->isEmpty()) {
                VectorEntity *vectorEntity = layer->get();
                painter.setPen(getPen(vectorEntity->getStroke()));
                if(vectorEntity != 0) {
                    switch(vectorEntity->getType()) {
                        case VectorEntity::RECTANGLE:
                            paintVectorEntity((Rectangle*) vectorEntity, &painter);
                            break;
                        case VectorEntity::CIRCLE:
                            paintVectorEntity((Circle*) vectorEntity, &painter);
                            break;
                        case VectorEntity::PATH:
                            paintVectorEntity((Path*) vectorEntity, &painter);
                            break;
                        default: break;
                    }
                } 
            }
        }

    }
}

void Canvas::paintVectorEntity(const Rectangle *rectangle, QPainter *painter)
{
    const QPoint* a = rectangle->getPointA();
    const QPoint* b = rectangle->getPointB();
    QPainterPath rectPath;
    rectPath.moveTo(*a);
    rectPath.lineTo(QPoint(a->x(),b->y()));
    rectPath.lineTo(*b);
    rectPath.lineTo(QPoint(b->x(),a->y()));
    rectPath.closeSubpath();

    painter->fillPath(rectPath, getBrush(rectangle->getBackground()));
    painter->drawPath(rectPath);
    paintControlPoints(rectangle, painter);
}

void Canvas::paintVectorEntity(const Circle *circle, QPainter *painter)
{
    const QPoint* center = circle->getPointCenter();
    const QPoint* border = circle->getPointBorder();
    QPainterPath ellipsePath;

    int diffx = abs(center->x() - border->x());
    int diffy = abs(center->y() - border->y());
    
    int max = diffx;
    int min = diffy;
    if(diffy > max) {
        max = diffy;
    } else {
        min = diffx;
    }

    ellipsePath.addEllipse(*center, max, max);

    painter->fillPath(ellipsePath, getBrush(circle->getBackground()));
    painter->drawPath(ellipsePath);
    paintControlPoints(circle, painter);
}

void Canvas::paintVectorEntity(const Path *path, QPainter *painter)
{
    const QList<QPoint>* points = path->getControlPoints();
    if(points->size() > 0) {
        QPainterPath paintedPath;
        paintedPath.moveTo(points->first());
        for(int i = 1; i < points->size(); i++) {
            paintedPath.lineTo(points->at(i));
        }

        painter->drawPath(paintedPath);
        paintControlPoints(path, painter);
    }
}

void Canvas::paintControlPoints(const VectorEntity *vectorEntity, QPainter *painter)
{
    const QList<QPoint>* points = vectorEntity->getControlPoints();
    painter->setPen(controlPointPen);
    for(int i = 0; i < points->size(); i++) {
        const QPoint *point = &points->at(i);
        QPainterPath pointPath;
        pointPath.addEllipse(*point, 10, 10);
        painter->fillPath(pointPath, controlPointBrush);
        painter->drawPath(pointPath);
    }
}

QPen Canvas::getPen(const Stroke &stroke)
{
    Qt::PenStyle style;
    switch(stroke.getType()) {
        case Stroke::DASHED: style = Qt::DashLine; break;
        case Stroke::DOTTED: style = Qt::DotLine; break;
        case Stroke::SOLID:
        default:
            style = Qt::SolidLine;
    }

    return QPen(*(stroke.getColor()), stroke.getSize(), style, Qt::RoundCap, Qt::RoundJoin);
}

QBrush Canvas::getBrush(const Background &background)
{
    return QBrush(background.getColor(), Qt::SolidPattern);
}


/**
 * -------------------------------------------------------------
 *  core - events
 * -------------------------------------------------------------
 */


void Canvas::mousePressEvent(QMouseEvent *e)
{
    if(layerController == 0 || toolController == 0) {
        return;
    } else if(layerController->getLayers()->isEmpty()) {
        return;
    }

    toolController->mousePressEvent(e);
}

void Canvas::mouseMoveEvent(QMouseEvent *e)
{
    if(layerController == 0 || toolController == 0) {
        return;
    } else if(layerController->getLayers()->isEmpty()) {
        return;
    }

    toolController->mouseMoveEvent(e);
}

void Canvas::mouseReleaseEvent(QMouseEvent *e)
{
    if(layerController == 0 || toolController == 0) {
        return;
    } else if(layerController->getLayers()->isEmpty()) {
        return;
    }

    toolController->mouseReleaseEvent(e);
}

void Canvas::updateView()
{
    update();
}
