#include "apiespacesverts.h"

ApiEspacesVerts::ApiEspacesVerts()
{

}

int ApiEspacesVerts::getId()
{
    return ESPACES_VERTS;
}

QPixmap ApiEspacesVerts::getPixmap()
{
    return QPixmap(":/Icons/iconespacesverts.png");
}

void ApiEspacesVerts::API_Call()
{
    manApiEspacesVerts = new QNetworkAccessManager(this);
    connect(manApiEspacesVerts, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
    manApiEspacesVerts->get(QNetworkRequest(QUrl("https://opendata.paris.fr/api/records/1.0/search/?dataset=espaces_verts&rows=-1&sort=-nsq_espace_vert&facet=type_ev&facet=id_division&facet=adresse_codepostal&facet=ouvert_ferme&facet=id_atelier_horticole&facet=competence&facet=categorie&facet=presence_cloture&facet=proprietaire&facet=gestionnnaire")));
}

void ApiEspacesVerts::API_Results(QNetworkReply *reply)
{
    m_list.clear();

    document = QJsonDocument::fromJson(reply->readAll());
    jsonObject = document.object();
    jsonArray = jsonObject["records"].toArray();
    for(QJsonValue val:jsonArray){
        jsObj = val.toObject();

        geoloc = jsObj["fields"].toObject()["geom_x_y"].toArray();
        double lat = geoloc[0].toDouble();
        double longit = geoloc[1].toDouble();

        GeoObj geo;

        geo.longitude = longit;
        geo.latitude = lat;      
        geo.pixmap = Icon::iconMapOff(getPixmap(), QColor(126, 170, 44));

//        geo.pixmap = QPixmap();

        //geo.id = getId();

        m_list << geo;
    }

    emit callFinished(m_list, ESPACES_VERTS);
    reply->deleteLater();
}

void ApiEspacesVerts::getInfo()
{
    API_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}
