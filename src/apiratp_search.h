#ifndef APIRATP_SEARCH_H
#define APIRATP_SEARCH_H

#include "Abstract_API.h"
#include "apiratp_global.h"
#include "uiratp.h"

#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

class ApiRatp_Search : public Abstract_API
{
public:
    ApiRatp_Search();
    int getId() override;
    QPixmap getPixmap() override;

    ApiRatp_Global *ratpGlobal;
    Uiratp *uiratp;

    QNetworkAccessManager *managerUni;
    QNetworkRequest *requestUni;
    QNetworkReply *replyUni;

public slots:
    void DoUniRequest();
    void getInfo() override;

private:
    void replyFinishedUni();
};

#endif // APIRATP_SEARCH_H
