#ifndef UISTATION_H
#define UISTATION_H

#include <QDateTime>
#include <QDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class UiStation;
}

class UiStation : public QDialog
{
    Q_OBJECT

public:
    explicit UiStation(QWidget *parent = nullptr);
    ~UiStation();

    QNetworkAccessManager *managerStation;
    QNetworkRequest *requestStation;
    QNetworkReply *replyStation;

    void DoStationRequest();
private:
    Ui::UiStation *ui;

    void PeriStifJson();
    void showFinishedStation(QJsonArray);
    void CleanView();

private slots:
    void replyFinishedStation();
    void ChangePage();
};

#endif // UISTATION_H
