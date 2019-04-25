#ifndef STOPPOINT_H
#define STOPPOINT_H

#include <QPointF>
#include <QString>



class StopPoint
{
public:
    StopPoint(QString sp_externalcodeline, QString sp_nomzde, QString sp_monorefzde, QString sp_idzde, QPointF sp_coordszde, int sp_myIndex);

    QString externalcodeLine;
    QString nomZDE;
    QString monoRefZDE;
    QString idZDE;
    QPointF coordsZDE;
    int myIndex;

    static bool compareStopPoint(const StopPoint &sp1, const StopPoint &sp2);
};

#endif // STOPPOINT_H
