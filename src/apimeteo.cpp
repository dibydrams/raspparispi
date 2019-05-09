#include "apimeteo.h"
#include "indiceuv.h"
#include "QNetworkAccessManager"

ApiMeteo::ApiMeteo()
{

}

Abstract_API::API_index ApiMeteo::getId()
{
    return METEO;
}

QPixmap ApiMeteo::getPixmap()
{
    return QPixmap(":/Icons_meteo/meteo4.png");
}

void ApiMeteo::API_Call()
{

    API_Access = new QNetworkAccessManager(this);

    m_meteo = new  meteo;
    p_pollution = new Pollution;
    i_indice = new IndiceUV;
    pm_prevision = new Prevision;

    m_meteo->setRequest();
    p_pollution->setRequest();
    i_indice->setRequest();
    pm_prevision->setRequest();

    /*connect(m_meteo, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
    connect(p_pollution, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
    connect(i_indice, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
    connect(pm_prevision, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));*/

}

void ApiMeteo::API_Results(QNetworkReply *)
{

    m_list.clear(); // Reset de la liste de GeoObj à chaque passage dans la fonction


        GeoObj geo;

        geo.longitude = 2.35;
        geo.latitude = 48.86;
        geo.pixmap = QPixmap();

        m_list << geo;

}




void ApiMeteo::getInfo()
{
    API_Call();
}


