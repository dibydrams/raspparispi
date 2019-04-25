#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QString>


class Transport
{
public:
    Transport(QString t_externalcode_line, QString t_shortNameLine, QString t_shortGroupOfLines, QString t_networkName, QString t_transportMode, int t_accessibility, int myIndex);
    enum Modes
    {
        bus,
        funicular,
        metro,
        rail,
        tram
    };
    Modes mode;
    QString codeLine;
    QString shortNameLine;
    QString shortGroupOfLines;
    QString networkName;
    Modes transportMode;
    int accessibility;
    QString nameShowed;
    int myIndex;

    static bool compareTransports(const Transport &t1, const Transport &t2);
    Transport::Modes StringToEnum(QString _strMode);
};

#endif // TRANSPORT_H
