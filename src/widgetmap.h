#ifndef WIDGETMAP_H
#define WIDGETMAP_H
/*
< la carte s.v.p >
 ----------------
  \
   \
       __
      UooU\.'@@@@@@`.
      \__/(@@@@@@@@@@)
           (@@@@@@@@)
           `YY~~~~YY'
            ||    ||


description:

A travers l'API Tomtom (https://api.tomtom.com/map/1/staticimage) :
télécharge une zone de la carte par ses coordonnées gps au centre,
puis la stocke près du fichier de configuation RasParispi.conf
du répertoire .config/AJC_Linux_embarque/

La carte.png est lancée localement à la prochaine execution
du programme avec ses caractéristiques enregistrées.

Les coordonnées gps des points d'intérets (API's diverses) sont
converties en coordonnées pixels pour être affichés sur la carte.

licence: GPLv3
*/

#include <QSettings>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QHash>
#include <QString>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QBuffer>
#include <QFile>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPainter>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPoint>
#include <QPointF>
#include <QDir>
#include <QDebug>
#include <QWidget>
#include <Abstract_API.h>


class WidgetMap : public QWidget
{
public:
    double m_centreLongitude;
    double m_centreLatitude;
    double m_rayonCentre;
    double m_BBOXminLongitude;
    double m_BBOXminLatitude;
    double m_BBOXmaxLongitude;
    double m_BBOXmaxLatitude;
    double m_compensationLargeurRayon;
    int m_largeurImage;
    int m_hauteurImage;
    int m_zoom;
    int m_flagClic;

    QString m_fichierCarte;
    QSettings *m_settings;
    QPoint m_pointClicSouris;
    QPixmap pix_PI;

    QList<Abstract_API::GeoObj> m_listePI;
    QList<QList<Abstract_API::GeoObj>> m_listePI_API;
    QList<QList<QPoint>> m_listePixelPoint;

    explicit WidgetMap(QWidget *parent = nullptr);
    int InitSetting(QSettings *settings, const QString key, const QString value, QVariant &var);

    ~WidgetMap() override;
private:
    void paintEvent(QPaintEvent *event) override;
    int m_iconCount;

protected:
        virtual void mousePressEvent(QMouseEvent *event) override;

signals:
        void clicIcon();
};

#endif // WIDGETMAP_H
