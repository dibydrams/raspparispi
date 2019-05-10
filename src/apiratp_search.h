#ifndef APIRATP_SEARCH_H
#define APIRATP_SEARCH_H

#include "Abstract_API.h"
#include "apiratp_global.h"

#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

class ApiRatp_Search : public Abstract_API
{
    Q_OBJECT

public:
    ApiRatp_Search();
    API_index getId() override;
    QPixmap getPixmap() override;

    ApiRatp_Global *ratpGlobal;

    QNetworkAccessManager *managerUni;
    QNetworkRequest *requestUni;
    QNetworkReply *replyUni;

public slots:
    void getInfo() override;

    void DoUniRequest(QString _transport, QString _station);
private:
    void replyFinishedUni();

signals:
    void ShowErrorUni(QString);
    void ShowFinishedUni(QJsonArray);
};

#endif // APIRATP_SEARCH_H
