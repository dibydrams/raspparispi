#include "stoppoint.h"

StopPoint::StopPoint(QString sp_codeline, QString sp_nomzde, QString sp_monorefzde, QString sp_idzde, QPointF sp_coordszde)
{
    codeLine = sp_codeline;
    nomZDE = sp_nomzde;
    monoRefZDE = sp_monorefzde;
    idZDE = sp_idzde;
    coordsZDE = sp_coordszde;
}
