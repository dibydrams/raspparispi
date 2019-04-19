#ifndef STOPPOINT_H
#define STOPPOINT_H

#include <QPointF>
#include <QString>



class StopPoint
{
public:
    StopPoint(QString sp_codeline, QString sp_nomzde, QString sp_monorefzde, QString sp_idzde, QPointF sp_coordszde);

    QString codeLine;
    QString nomZDE;
    QString monoRefZDE;
    QString idZDE;
    QPointF coordsZDE;
};

#endif // STOPPOINT_H
