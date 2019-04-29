#include "widgetmap.h"
#include <QPainter>
#include <QSettings>
#include <QDebug>

// initialise les valeurs de .config/AJC_Linux_embarque/RasParispi.conf si elles n'existent pas
// et les renvoient si elle existent

int WidgetMap::InitSetting( QSettings *settings, const QString key, const QString value, QVariant &var )
{
    if( !QFile::exists(settings->fileName())) settings->setValue(key, value);
    else if(settings->value(key, value).toString() == nullptr) settings->setValue(key, value);
    else {
        var = settings->value(key, 0);
        return 1;
    }
    return 0;
}

WidgetMap::WidgetMap(QWidget *parent) : QWidget(parent)
{

    // initialise les valeurs de .config/AJC_Linux_embarque/RasParispi.conf si elles n'existent pas
    //

    m_settings = new QSettings("AJC_Linux_embarque", "RasParispi");

    // valeurs de départ par defaut au centre de Paris

    if( !QFile::exists(m_settings->fileName()))
    {
        m_centreLongitude = 2.341139;//2.3345019;
        m_centreLatitude = 48.865689;//48.859114;
        m_rayonCentre = 0.008;
        m_zoom = 15; // zoom inférieur à 18 sinon l'api tomtom retourne une erreur: carte trop grande
    }
    m_compensationLargeurRayon = 2;

    QVariant tmp;

    if(InitSetting(m_settings,"Coordonnees/centreLongitude", QString::number(m_centreLongitude,'f',13), tmp)) m_centreLongitude = tmp.toDouble();
    if(InitSetting(m_settings,"Coordonnees/centreLatitude", QString::number(m_centreLatitude,'f',13), tmp)) m_centreLatitude = tmp.toDouble();
    if(InitSetting(m_settings,"Coordonnees/rayonCentre", QString::number(m_rayonCentre,'f',3), tmp)) m_rayonCentre = tmp.toDouble();
    if(InitSetting(m_settings,"Image/largeur", "", tmp)) m_largeurImage = tmp.toInt();
    if(InitSetting(m_settings,"Image/hauteur", "", tmp)) m_hauteurImage = tmp.toInt();
    if(InitSetting(m_settings,"Image/zoom", QString::number(m_zoom), tmp) ) {
        m_zoom = tmp.toInt();
        if( m_zoom < 0 || m_zoom > 17 ) {
            // zoom inférieur à 18 sinon l'api tomtom retourne une erreur: carte trop grande
            m_zoom = 15;
            m_settings->setValue("Image/zoom", QString::number(15));
        }
    }
    if(InitSetting(m_settings,"Coordonnees/BBOXminLongitude", "", tmp)) m_BBOXminLongitude = tmp.toDouble();
    if(InitSetting(m_settings,"Coordonnees/BBOXminLatitude", "", tmp)) m_BBOXminLatitude = tmp.toDouble();
    if(InitSetting(m_settings,"Coordonnees/BBOXmaxLongitude", "", tmp)) m_BBOXmaxLongitude = tmp.toDouble();
    if(InitSetting(m_settings,"Coordonnees/BBOXmaxLatitude", "", tmp)) m_BBOXmaxLatitude = tmp.toDouble();

    // emplacement du fichier carte au même niveau du dossier de config
    // .config/AJC_Linux_embarque/carte.png

    m_fichierCarte = m_settings->fileName();
    m_fichierCarte = m_fichierCarte.leftRef(m_fichierCarte.lastIndexOf('/',-2)).toString();
    m_fichierCarte.append("/carte.png");

    if( !QFile::exists(m_fichierCarte))
    {
        // calcul du boundingBox de l'api tomtom
        // selon le gps du centre de la carte et d'un rayon (en dégré)
        // le rayon est compensé en largeur pour obtenir une carte de forme rectangulaire
        // (longitude de -90 degrés à +90 degrés, latitude de -180 degrés à +180 degrés)

        m_BBOXminLongitude = m_centreLongitude - (m_rayonCentre*m_compensationLargeurRayon);
        m_BBOXminLatitude = m_centreLatitude - m_rayonCentre;
        m_BBOXmaxLongitude = m_centreLongitude + (m_rayonCentre*m_compensationLargeurRayon);
        m_BBOXmaxLatitude = m_centreLatitude + m_rayonCentre;

        // téléchargement d'une zone carte sur l'api tomtom
        //

        QNetworkAccessManager mgr;
        QEventLoop eventLoop;

        // à la requête finished() de l'api tomtom, eventLoop "quit()" sa boucle d'attente

        QObject::connect(&mgr, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));

        QString urlText(
            "https://api.tomtom.com/map/1/staticimage?"
            "key=8bUkGqzvXEZzyqvqFnbw0JoTfPk7BFQ8&"
            "format=png&"
            "layer=basic&style=main&view=Unified&"
            "zoom=" + QString::number(m_zoom) + "&"

            "bbox=" + QString::number(m_BBOXminLongitude,'f',13) + ","
                    + QString::number(m_BBOXminLatitude,'f',13)  + ","
                    + QString::number(m_BBOXmaxLongitude,'f',13) + ","
                    + QString::number(m_BBOXmaxLatitude,'f',13)
        );

        QNetworkRequest req( (QUrl( urlText )) );

        QNetworkReply *reply = mgr.get(req);

        eventLoop.exec(); // boucle d'attente jusqu'au signal finished()

        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();

            QBuffer *buf = new QBuffer;
            buf->setBuffer(&data);
            buf->open(QIODevice::ReadOnly);

            QPixmap *pixmap = new QPixmap;

            pixmap->loadFromData(buf->buffer(), "PNG", Qt::AutoColor);

            QImage image = pixmap->toImage();

            // enregistrement .config/AJC_Linux_embarque/carte.png

            if( !image.save(m_fichierCarte)) qDebug() << "erreur de sauvegarde: " << m_fichierCarte;
            else {

                m_largeurImage = pixmap->height();
                m_hauteurImage = pixmap->width();

                // mise à jour du fichier de config

                InitSetting(m_settings,"Coordonnees/BBOXminLongitude", QString::number(m_BBOXminLongitude,'f',13), tmp);
                InitSetting(m_settings,"Coordonnees/BBOXminLatitude", QString::number(m_BBOXminLatitude,'f',13), tmp);
                InitSetting(m_settings,"Coordonnees/BBOXmaxLongitude", QString::number(m_BBOXmaxLongitude,'f',13), tmp);
                InitSetting(m_settings,"Coordonnees/BBOXmaxLatitude", QString::number(m_BBOXmaxLatitude,'f',13), tmp);
                InitSetting(m_settings,"Image/largeur", QString::number(m_largeurImage), tmp);
                InitSetting(m_settings,"Image/hauteur", QString::number(m_hauteurImage), tmp);
            }
        }
        else qDebug() << "erreur api tomtom: " << reply->errorString();

        delete reply;
    }
}


void WidgetMap::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QPixmap carte(m_fichierCarte);
    p.drawPixmap(0,0,carte);

//    // icone au centre de la carte

//    QString fileName = ":/Icons/bonhomme.png";
//    QPixmap pixmap(fileName);
//    p.drawPixmap(carte.width()/2,carte.height()/2,pixmap);

//        // tests 3 coord gps

//        Abstract_API::GeoObj geo1, geo2, geo3;

//        geo1.longitude = 2.33;
//        geo1.latitude = 48.86;
//        geo1.pixmap = QPixmap();
//        geo1.id = 0;

//        geo2.longitude = 2.335;
//        geo2.latitude = 48.865;
//        geo2.pixmap = QPixmap();
//        geo2.id = 1;

//        geo3.longitude = 2.32;
//        geo3.latitude = 48.862;
//        geo3.pixmap = QPixmap();
//        geo3.id = 3;

//        m_listePI << geo1 << geo2 << geo3;

        int resultatPixelPointX;
        int resultatPixelPointY;

        double distanceLongitude = abs(m_BBOXmaxLongitude - m_BBOXminLongitude);
        double distanceLatitude = abs(m_BBOXmaxLatitude - m_BBOXminLatitude);

        double coefficient_X = carte.width() / distanceLongitude;
        double coefficient_Y = carte.height() / distanceLatitude;

        QPixmap pix_PI(":/Icons/point_interet.png");

        for (int i = 0; i < m_listePI.size(); i++)
        {
            qDebug() << "longitude " << m_listePI.at(i).longitude;
            qDebug() << "latitude " << m_listePI.at(i).latitude;

            resultatPixelPointX = static_cast<int> ((m_listePI.at(i).longitude - m_BBOXminLongitude) * coefficient_X);
            resultatPixelPointY = static_cast<int> ((m_listePI.at(i).latitude - m_BBOXminLatitude) * coefficient_Y);

            // inversion de l'axe verticale pixel par rapport au sens de l'axe latitude
            resultatPixelPointY = carte.height() - resultatPixelPointY;

            qDebug() << "X :" << resultatPixelPointX << "Y :" << resultatPixelPointY;

            if( m_listePI.at(i).pixmap.isNull() ) p.drawPixmap(resultatPixelPointX,resultatPixelPointY,pix_PI);
            else p.drawPixmap(resultatPixelPointX,resultatPixelPointY,m_listePI.at(i).pixmap);

//            QString affCoord;
//            affCoord = QString::number(m_listePI.at(i).longitude, 'f', 13) + "  " + QString::number(m_listePI.at(i).latitude, 'f', 13);

//            p.drawText(resultatPixelPointX+10,resultatPixelPointY+40,affCoord);


        }
}

void WidgetMap::dataReceived(QList<Abstract_API::GeoObj> list)
{
    //this->update();
}

WidgetMap::~WidgetMap()
{
    delete m_settings;
}
