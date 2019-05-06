#include "stoppoint.h"

StopPoint::StopPoint(QString sp_codeline, QString sp_nomzde, QString sp_monorefzde, QString sp_idzde, QPointF sp_coordszde, QString sp_networkname, int sp_myindex)
{
    externalcodeLine = sp_codeline;
    nomZDE = sp_nomzde;
    monoRefZDE = sp_monorefzde;
    idZDE = sp_idzde;
    coordsZDE = sp_coordszde;
    networkName = sp_networkname;
    myIndex = sp_myindex;
}

bool StopPoint::compareStopPoint(const StopPoint &sp1, const StopPoint &sp2)
{
    if(sp1.nomZDE != sp2.nomZDE)
    {
        return sp1.nomZDE < sp2.nomZDE;
    }
    return 0;
}
