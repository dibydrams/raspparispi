#include "Abstract_API.h"


Abstract_API::Abstract_API(QObject *parent) : QObject(parent)
{

}


// Aide au Debug, si nécessaire. Cette fonction peut être customisée à souhait si besoin
void Abstract_API::debug(QList <GeoObj> m_list)
{
    for (auto i : m_list) {
        qDebug() << i.longitude;
        qDebug() << i.latitude;
        qDebug() << i.pixmap;
        qDebug() << i.id;
    }
}


