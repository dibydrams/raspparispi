#include "apivigicrues.h"

apiVigiCrues::apiVigiCrues()
{

}

void apiVigiCrues::API_Call()
{
    API_AccessVigi = new QNetworkAccessManager(this);

    h_hauteur = new VigiCruesHauteur;
    d_debit = new VigiCruesDebit;

    h_hauteur->setRequest();
    d_debit->setRequest();

}

void apiVigiCrues::API_Results(QNetworkReply *reply)
{
    m_list.clear();

    GeoObj geo;

    geo.longitude = 2.37;
    geo.latitude = 48.84;

    m_list << geo;
}

void apiVigiCrues::getInfo()
{
    API_Call();
}

Abstract_API::API_index apiVigiCrues::getId()
{
    return CRUES;
}

QPixmap apiVigiCrues::getPixmap()
{
    return QPixmap(":/Icons/floodicon.png");
}
