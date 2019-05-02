#include "theatre.h"

theatre::theatre()
{

}

int theatre::getId()
{
    return THEATRE;
}

QPixmap theatre::getPixmap()
{
    return QPixmap(":/Icons/theatre.png");
}

void theatre::theatreAPI_Call(){
    manager=new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("https://public.opendatasoft.com/api/records/1.0/search/?dataset=evenements-publics-cibul&q=theatre&rows=60&facet=tags&facet=placename&facet=department&facet=region&facet=city&facet=date_start&facet=date_end&facet=pricing_info&facet=updated_at&facet=city_district&refine.department=Paris&refine.date_start=2019&refine.tags=th%C3%A9%C3%A2tre&timezone=Europe%2FParis"));
    reply = manager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(readJsonTheatre()));
}

void theatre::readJsonTheatre(){
        m_list.clear();
        QByteArray responseBit = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(responseBit);
        QJsonObject replyObj = document.object();
        QJsonArray recordsJsonArray = replyObj["records"].toArray();

        foreach (const QJsonValue & value, recordsJsonArray) {
            QJsonObject obj = value.toObject();
            QJsonObject objectFields = obj["fields"].toObject();
            qDebug()<<"keys : : "<< objectFields.keys();
            qDebug()<<"title : : " << objectFields["title"].toString();
            qDebug()<<"address : : " << objectFields["address"].toString();
            qDebug()<<"dep : : "<< objectFields["department"].toString();
            qDebug()<<"hereherehrehrherehereherehereherehereherehereherehereherehereherehereh";
            //coordHelper.coordinates()
            QString adr=objectFields["address"].toString()+" "+objectFields["department"].toString();
            qDebug()<<" adresse : "<<adr;
            coordHelper=new addrToCoord(qApp,adr);
            qDebug()<<" coordonnées : : : :";
            qDebug()<<" latitude :: "<<coordHelper->getLatitude();
            qDebug()<< "longitude :: "<<coordHelper->getLongitude();
            double longitude=coordHelper->getLongitude();
            double latitude=coordHelper->getLatitude();
            coordHelper->deleteLater();
            // remplissage de geoObj
            GeoObj geo;
            geo.longitude = longitude;
            geo.latitude = latitude;
            geo.pixmap = QPixmap();
            m_list << geo;
        }
        emit callFinished(m_list, THEATRE);
}

void theatre::getInfo(){
    theatreAPI_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}


