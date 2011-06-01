/* 
 * File:   LayerController.h
 * Author: Ondrej Macoszek <macosond@fel.cvut.cz>
 *
 * Created on January 21, 2010, 3:18 PM
 */

#ifndef _LAYERCONTROLLER_H
#define	_LAYERCONTROLLER_H

#include <QtCore/QObject>
#include <QtCore/QList>

#include "business/entity/Layer.h"


class LayerController : public QObject
{
    Q_OBJECT
    
public:

    static int counter;

    LayerController(QObject *parent = 0);
    ~LayerController();

    QList<Layer*>* getLayers() const;
    Layer* getCurrentLayer();
    Layer* getLayerAt(int) const;

    int getCurrentLayerIndex() const;
    void setCurrentLayerIndex(int);
    bool isValidCurrentLayerIndex() const;
    bool isValidCurrentLayerIndex(int) const;
    void invalidateCurrentLayerIndex();

    bool isEmpty() const;
    void clear();

    void layerUp();
    void layerDown();
    void layerAdd();
    void layerRemove();
    void layerSelect(int);

public slots:
    void layerUpdated();

signals:
    void layerSelected(Layer *);
    void updated();

private:
    QList<Layer*> *layers;
    int currentLayerIndex;


};


#endif	/* _LAYERCONTROLLER_H */

