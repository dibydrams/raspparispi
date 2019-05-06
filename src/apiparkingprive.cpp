#include "apiparkingprive.h"

apiParkingPrive::apiParkingPrive()
{

}

apiParkingPrive::~apiParkingPrive()
{
    delete listParkingPrive;
}

Abstract_API::API_index apiParkingPrive::getId()
{
    return PARKING_PRIVE;
}

QPixmap apiParkingPrive::getPixmap()
{
    return QPixmap(":/Icons/iconparkingprive.png");
}

void apiParkingPrive::API_Results(QNetworkReply *reply)
{
    listGeoObj.clear();
    listParkingPrive->clear();
    QJsonDocument jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj = jsdoc.object();
    QJsonArray jsarr = jsobj["records"].toArray();

    for(QJsonValue jsval : jsarr){
        parkingPrive parking;
        GeoObj gObj;
        QJsonObject jsob = jsval.toObject();
        parking.name = jsob["fields"].toObject()["nom_parc"].toString();
        parking.address = jsob["fields"].toObject()["adress_geo"].toString();
        parking.tarif1h = jsob["fields"].toObject()["tf_1h_e"].toString();
        parking.horaire = jsob["fields"].toObject()["horaire_na"].toString();
        parking.plPMR = jsob["fields"].toObject()["nb_pl_pmr"].toInt();
        parking.plMoto = jsob["fields"].toObject()["nb_pl_moto"].toInt();
        parking.tarif1hMoto = jsob["fields"].toObject()["tmoto_1ehe"].toString();
        parking.velo = jsob["fields"].toObject()["acces_velo"].toString();
        parking.vElec = jsob["fields"].toObject()["v_elec_ch"].toString();
        parking.autopartage = jsob["fields"].toObject()["autopart"].toString();
        parking.hauteur = jsob["fields"].toObject()["h_parc_cm"].toInt();
        parking.latitude = jsob["fields"].toObject()["geo_shape"].toObject()["coordinates"].toArray()[1].toDouble();
        parking.longitude = jsob["fields"].toObject()["geo_shape"].toObject()["coordinates"].toArray()[0].toDouble();

        if(utilitaire::inMap(parking.latitude, parking.longitude)){
            listParkingPrive->append(parking);
            gObj.latitude = parking.latitude;
            gObj.longitude =parking.longitude;
            gObj.pixmap = Icon::iconMapOff(getPixmap(), Qt::red);

            listGeoObj << gObj;
        }
    }

    emit callFinished(listGeoObj, PARKING_PRIVE);
}

void apiParkingPrive::getInfo()
{
    networkManager = new QNetworkAccessManager(this);
    WidgetMap map;
    latCentre = QString::number(map.m_centreLatitude, 'g', 13);
    lonCentre = QString::number(map.m_centreLongitude, 'g', 13);
    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=parcs-de-stationnement-concedes-de-la-ville-de-paris&rows=-1&facet=acces_vl&facet=arrdt&facet=deleg&facet=h_parc_cm&facet=type_parc&facet=horaire_na&facet=asc_surf&facet=acces_moto&facet=acces_velo&facet=v_elec_ch&facet=autopart&facet=tarif_pr&facet=tarif_res&facet=tf_pr_moto&facet=tf_res_mo&facet=parc_amod&facet=parc_relai&geofilter.distance="+latCentre+"%2C"+lonCentre+"%2C"+rayon);
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_Results(QNetworkReply*)));
    QApplication::setOverrideCursor(Qt::WaitCursor);
}
