#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "stoppoint.h"

#include <QList>
#include <QString>


class Transport
{
public:
    Transport(QString t_externalcode_line, QString t_shortNameLine, QString t_shortGroupOfLines, QString t_networkName, QString t_transportMode, int t_accessibility, int myIndex, QList<StopPoint> t_mySPList);
    enum Modes
    {
        bus,
        funicular,
        metro,
        rail,
        tram
    };
    QString codeLine;
    QString shortNameLine;
    QString shortGroupOfLines;
    QString networkName;
    Modes transportMode;
    int accessibility;
    QString nameShowed;
    int myIndex;
    QList<StopPoint> mySPList;

    static bool compareTransports(const Transport &t1, const Transport &t2);
    Transport::Modes StringToEnum(QString _strMode);

private:
    Modes mode;
};

#endif // TRANSPORT_H
