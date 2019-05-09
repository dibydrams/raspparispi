#ifndef UIRATP_H
#define UIRATP_H

#include "apiratp_global.h"
#include "apiratp_search.h"

#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QJsonArray>
#include <QJsonObject>

namespace Ui {
class Uiratp;
}

class Uiratp : public QDialog
{
    Q_OBJECT

public:
    explicit Uiratp(QWidget *parent = nullptr);
    ~Uiratp();

    ApiRatp_Global ratpGlobal;
    ApiRatp_Search ratpSearch;

private slots:
    void SetUniTransportIndex(int _codeT);
    void SetUniStationIndex(int _codeS);
    void ShowErrorUni(QString);
    void ShowFinishedUni(QJsonArray);
    void ShowTransports();
    void ShowTransportStopPoints(int _code);
    void PrepareUniRequest();

private:
    Ui::Uiratp *ui;

    void CleanView();
};

#endif // UIRATP_H
