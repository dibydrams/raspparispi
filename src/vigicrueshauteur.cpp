#include "vigicrueshauteur.h"

VigiCruesHauteur::VigiCruesHauteur()
{
    setRequest();
    connect(manager,&QNetworkAccessManager::finished,this,&VigiCruesHauteur::replyFinished);
}

void VigiCruesHauteur::setRequest()
{
    manager = new QNetworkAccessManager(this);
    QUrl url("http://hubeau.eaufrance.fr/api/v1/hydrometrie/observations_tr?bbox=2.363348007202149%2C48.84285889094348%2C2.368412017822266%2C48.84669988998153&code_entite=F700000103&date_debut_obs=2019-05-09&distance=10&grandeur_hydro=H&latitude=48.861469422154464&longitude=2.34630372400731&size=200&sort=asc");
    request.setUrl(url);
    reply = manager->get(request);
}

QHash<QString, QVariant> VigiCruesHauteur::readJson()
{
    QHash <QString, QVariant> hash;

    QJsonDocument d = QJsonDocument::fromJson(req);
    QJsonObject obj = d.object();

    QJsonArray jsonArr;
    jsonArr = obj["data"].toArray();

    for (int i = 0; i < jsonArr.size(); i++) {

        QJsonObject obj2 = jsonArr[i].toObject();
        //QJsonValue val = obj2.value(QString("main"));
        //QJsonObject item = val.toObject();
        hash[QString ("date_obs%1").arg(i)]=obj2.value("date_obs").toString();
        hash[QString ("resultat_obs%1").arg(i)] = obj2.value("resultat_obs").toDouble();
        hash[QString ("echcount")] = jsonArr.size();
}

    return hash;
}

void VigiCruesHauteur::replyFinished()
{
    req=reply->readAll();
    pm_hash=readJson();
    emit received();
}
