
#include "Layer.h"

/**
 * -------------------------------------------------------------
 *  constructors
 * -------------------------------------------------------------
 */

Layer::Layer(QObject *parent) : QObject(parent)
{
    vectorEntity = 0;
    name = QString("empty");
}

Layer::~Layer()
{
    if(vectorEntity != 0) {
        delete vectorEntity;
    }
}

//Layer::Layer(const Layer &other)
//{
//    copyObject(other);
//}
//
//Layer& Layer::operator=(const Layer &other)
//{
//    copyObject(other);
//    return *this;
//}
//
//void Layer::copyObject(const Layer& other)
//{
//    VectorEntity *othVE = other.get();
//    if(othVE != 0) {
//        vectorEntity = new VectorEntity(*othVE);
//    }
//    name = other.getName();
//}

/**
 * -------------------------------------------------------------
 *  core
 * -------------------------------------------------------------
 */

void Layer::add(VectorEntity* _vectorEntity)
{
    if(vectorEntity != 0) {
        delete vectorEntity;
    }
    vectorEntity = _vectorEntity;
    vectorEntity->setParent(this);
    connect(vectorEntity, SIGNAL(updated()),
            this, SLOT(update()));
    setName(vectorEntity->getName());
    emit updated();
}

VectorEntity* Layer::get() const
{
    return vectorEntity;
}

bool Layer::isEmpty() const
{
    return (vectorEntity == 0);
}

QString Layer::getName() const
{
    return name;
}

void Layer::setName(const QString &_name)
{
    name = _name;
}


/**
 * -------------------------------------------------------------
 *  layer - slots
 * -------------------------------------------------------------
 */

void Layer::update()
{
    if(vectorEntity != 0) {
        setName(vectorEntity->getName());
    }
    emit updated();
}