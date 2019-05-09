#include "widgetmap.h"
#include "dialoginfo.h"
#include <cmath>
#include <QPainter>
#include <QSettings>
#include <QDebug>

// valeurs de départ par defaut au centre de Paris

double WidgetMap::centreLongitude = 2.34599; //6 rue rougemont
double WidgetMap::centreLatitude = 48.8699; //48.8716;
double WidgetMap::rayonCentre = 0.007129412; //0.006;
double WidgetMap::compensationLargeurRayon = 2.040087046;
int WidgetMap::zoom = 15;

double WidgetMap::BBOXminLongitude;
double WidgetMap::BBOXminLatitude;
double WidgetMap::BBOXmaxLongitude;
double WidgetMap::BBOXmaxLatitude;


// initialise les valeurs de .config/raspparispi/raspparispi.conf si elles n'existent pas
// et les renvoient si elles existent

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

void WidgetMap::setIconCount(int count)
{
    m_iconCount=count;
    // Remplissage de la iste vide m_listePI_API
            QList<Abstract_API::GeoObj> emptyL;
            for (int i = 0; i<m_iconCount; i++ ) {
                m_listePI_API << emptyL;
            }
}

WidgetMap::WidgetMap(QWidget *parent) : QWidget(parent)
{

    // initialise les valeurs de .config/raspparispi/raspparispi.conf si elles n'existent pas
    //

    m_settings = new QSettings("raspparispi", "raspparispi");

    // valeurs de départ par defaut au centre de Paris

    int flagConfigVide = 0;

    if(!QFile::exists(m_settings->fileName()))
    {
        m_centreLongitude = centreLongitude; //2.34599;//6 rue rougemont
        m_centreLatitude = centreLatitude; //48.8699;//48.8716;
        m_rayonCentre = rayonCentre; //0.007129412;//0.006;
        m_zoom = zoom; //15; // zoom inférieur à 18 sinon l'api tomtom retourne une erreur: carte trop grande
        flagConfigVide = 1;
    }

    m_compensationLargeurRayon = compensationLargeurRayon;//2.040087046;//2;

    QVariant tmp;

    if(InitSetting(m_settings,"Coordonnees/centreLongitude", QString::number(m_centreLongitude,'f',13), tmp))
        if(!flagConfigVide) m_centreLongitude = centreLongitude = tmp.toDouble();
    if(InitSetting(m_settings,"Coordonnees/centreLatitude", QString::number(m_centreLatitude,'f',13), tmp))
        if(!flagConfigVide) m_centreLatitude = centreLatitude = tmp.toDouble();
    if(InitSetting(m_settings,"Coordonnees/rayonCentre", QString::number(m_rayonCentre,'f',13), tmp))
        if(!flagConfigVide) m_rayonCentre = rayonCentre = tmp.toDouble();
    //if(InitSetting(m_settings,"Coordonnees/compensationLargeurRayon", QString::number(m_compensationLargeurRayon,'f',13), tmp))
        //if(!flagConfigVide) m_compensationLargeurRayon = compensationLargeurRayon = tmp.toDouble();
    //if(InitSetting(m_settings,"Image/largeur", "", tmp)) m_largeurImage = tmp.toInt();
    //if(InitSetting(m_settings,"Image/hauteur", "", tmp)) m_hauteurImage = tmp.toInt();
    if(InitSetting(m_settings,"Coordonnees/zoom", QString::number(m_zoom), tmp) ) {
        m_zoom = zoom = tmp.toInt();
        if( m_zoom < 0 || m_zoom > 17 ) {
            // zoom inférieur à 18 sinon l'api tomtom retourne une erreur: carte trop grande
            m_zoom = zoom; //15;
            m_settings->setValue("Image/zoom", QString::number(15));
        }
    }
    //if(InitSetting(m_settings,"Coordonnees/BBOXminLongitude", "", tmp)) m_BBOXminLongitude = tmp.toDouble();
    //if(InitSetting(m_settings,"Coordonnees/BBOXminLatitude", "", tmp)) m_BBOXminLatitude = tmp.toDouble();
    //if(InitSetting(m_settings,"Coordonnees/BBOXmaxLongitude", "", tmp)) m_BBOXmaxLongitude = tmp.toDouble();
    //if(InitSetting(m_settings,"Coordonnees/BBOXmaxLatitude", "", tmp)) m_BBOXmaxLatitude = tmp.toDouble();

    // emplacement du fichier carte au même niveau du dossier de config
    // .config/raspparispi/carte.png

    m_fichierCarte = m_settings->fileName();
    m_fichierCarte = m_fichierCarte.leftRef(m_fichierCarte.lastIndexOf('/',-2)).toString();
    m_fichierCarte.append("/carte.png");

    if( 1/*!QFile::exists(m_fichierCarte)*/)
    {
        // calcul du boundingBox de l'api tomtom
        // selon le gps du centre de la carte et d'un rayon (en dégré)
        // le rayon est compensé en largeur pour obtenir une carte de forme rectangulaire
        // (longitude de -90 degrés à +90 degrés, latitude de -180 degrés à +180 degrés)

        m_BBOXminLongitude = m_centreLongitude - (m_rayonCentre*m_compensationLargeurRayon);
        m_BBOXminLatitude = m_centreLatitude - m_rayonCentre;
        m_BBOXmaxLongitude = m_centreLongitude + (m_rayonCentre*m_compensationLargeurRayon);
        m_BBOXmaxLatitude = m_centreLatitude + m_rayonCentre;

        // test format hd 1920*1080 sans compensation en largeur
        //m_BBOXminLongitude = 2.325374833;
        //m_BBOXminLatitude = 48.86227647;
        //m_BBOXmaxLongitude = 2.366605167;
        //m_BBOXmaxLatitude = 48.87752353;

        // téléchargement d'une zone carte sur l'api tomtom
        //

        QNetworkAccessManager mgr;
        QEventLoop eventLoop;

        // à la requête finished() de l'api tomtom, eventLoop "quit()" sa boucle d'attente

        connect(&mgr, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));

        QString urlText(
            "http://api.tomtom.com/map/1/staticimage?"
            "key=8bUkGqzvXEZzyqvqFnbw0JoTfPk7BFQ8&"
            "format=png&"
            "layer=basic&style=main&view=Unified&"
            "zoom=" + QString::number(m_zoom) + "&"

            "bbox=" + QString::number(m_BBOXminLongitude,'f',13) + ","
                    + QString::number(m_BBOXminLatitude,'f',13)  + ","
                    + QString::number(m_BBOXmaxLongitude,'f',13) + ","
                    + QString::number(m_BBOXmaxLatitude,'f',13)
                );

       // qDebug()<<"url carte tomtom: " << urlText;
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

            // enregistrement .config/raspparispi/carte.png

            if( !image.save(m_fichierCarte)) qDebug() << "erreur de sauvegarde: " << m_fichierCarte;
            else {

                m_largeurImage = pixmap->width();
                m_hauteurImage = pixmap->height();

                // mise à jour du fichier de config

                //InitSetting(m_settings,"Coordonnees/BBOXminLongitude", QString::number(m_BBOXminLongitude,'f',13), tmp);
                //InitSetting(m_settings,"Coordonnees/BBOXminLatitude", QString::number(m_BBOXminLatitude,'f',13), tmp);
                //InitSetting(m_settings,"Coordonnees/BBOXmaxLongitude", QString::number(m_BBOXmaxLongitude,'f',13), tmp);
                //InitSetting(m_settings,"Coordonnees/BBOXmaxLatitude", QString::number(m_BBOXmaxLatitude,'f',13), tmp);
                //InitSetting(m_settings,"Image/largeur", QString::number(m_largeurImage), tmp);
                //InitSetting(m_settings,"Image/hauteur", QString::number(m_hauteurImage), tmp);

                BBOXminLongitude = m_BBOXminLongitude;
                BBOXminLatitude = m_BBOXminLatitude;
                BBOXmaxLongitude = m_BBOXmaxLongitude;
                BBOXmaxLatitude = m_BBOXmaxLatitude;

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

    int offsetCarteX, offsetCarteY;

    offsetCarteX = ((this->size().width()) - carte.width() ) / 2;
    offsetCarteY = ((this->size().height()) - carte.height() ) / 2;

    p.drawPixmap(offsetCarteX,offsetCarteY,carte);

    //// icone au centre de la carte
    QString fileName = ":/Icons/pin.png";
    QPixmap pixmapCentre(fileName);

    int decalagePointChaud_PinCentre_X, decalagePointChaud_PinCentre_Y;

    decalagePointChaud_PinCentre_X = pixmapCentre.width()/2;
    decalagePointChaud_PinCentre_Y = pixmapCentre.height();

    p.drawPixmap(((carte.width()/2)+offsetCarteX)-decalagePointChaud_PinCentre_X,
                 ((carte.height()/2)+offsetCarteY)-decalagePointChaud_PinCentre_Y,
                 pixmapCentre);

    int resultatPixelPointX;
    int resultatPixelPointY;

    double distanceLongitude = std::fabs(m_BBOXmaxLongitude - m_BBOXminLongitude);
    double distanceLatitude = std::fabs(m_BBOXmaxLatitude - m_BBOXminLatitude);

    double coefficient_X = carte.width() / distanceLongitude;
    double coefficient_Y = carte.height() / distanceLatitude;

    QPixmap pix_PI(":/Icons/point_interet.png");

    // calcul du hotspot du pixmap -> au milieu en bas du pixmap
    // (le hotspot du pointeur peut être donné en tant que position relative au coin supérieur gauche du pixmap)

    int decalagePixmapX = 0, decalagePixmapY = 0;
    int pixelPointPixmapX, pixelPointPixmapY;
    int cptAPI = 0;

    for (auto listePI_API : m_listePI_API)
    {
        if( (listePI_API.size() != 0) && listePI_API.first().pixmap.isNull() == false)
        {
            decalagePixmapX = listePI_API.first().pixmap.width()/2;
            decalagePixmapY = listePI_API.first().pixmap.height();
        }

        for ( auto elem : listePI_API )
        {
            resultatPixelPointX = static_cast<int> ((elem.longitude - m_BBOXminLongitude) * coefficient_X);
            resultatPixelPointY = static_cast<int> ((elem.latitude - m_BBOXminLatitude) * coefficient_Y);

            // inversion de l'axe verticale pixel par rapport au sens de l'axe latitude
            resultatPixelPointY = carte.height() - resultatPixelPointY;

            // prise en compte du hotspot du pixmap
            pixelPointPixmapX = resultatPixelPointX - decalagePixmapX;
            pixelPointPixmapY = resultatPixelPointY - decalagePixmapY;

            //qDebug() << "X :" << resultatPixelPointX << "Y :" << resultatPixelPointY;

            // affiche les points d'intérets uniquement à l'intérieur de la carte

            if(resultatPixelPointX>=0 && resultatPixelPointX<m_largeurImage
                    && resultatPixelPointY>=0 && resultatPixelPointY<m_hauteurImage)
            {
                // offset carte pour centrer au centre du qwidget
                resultatPixelPointX += offsetCarteX;
                resultatPixelPointY += offsetCarteY;
                pixelPointPixmapX += offsetCarteX;
                pixelPointPixmapY += offsetCarteY;

                if( elem.pixmap.isNull()) p.drawPixmap(resultatPixelPointX,resultatPixelPointY,pix_PI);
                else p.drawPixmap(pixelPointPixmapX,pixelPointPixmapY,elem.pixmap);


                if( m_flagClic)
                {
                    //qDebug() << " " << pixelPointPixmapX << " " << pixelPointPixmapX + elem.pixmap.width();
                    //qDebug() << " " << pixelPointPixmapY << " " << pixelPointPixmapY + elem.pixmap.height();

                    if( (m_pointClicSouris.x() >= pixelPointPixmapX) && (m_pointClicSouris.x() <= pixelPointPixmapX + elem.pixmap.width()) &&
                        (m_pointClicSouris.y() >= pixelPointPixmapY) && (m_pointClicSouris.y() <= pixelPointPixmapY + elem.pixmap.height()) )
                    {
                        /*Le qDebug ci dessous permet lors du clic de la souris, d'afficher les informations*/
                        //qDebug() <<"here papy !: :"<< elem.info.values();
                        listeInfoGeoObj << elem;
                    }
                }
            }
        }
        cptAPI ++;
    }
    m_flagClic = 0;
}

void WidgetMap::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
       // listeInfoGeoObj.clear();
        QString text = "Dernier clic : Position : (" + QString::number(event->x()) + ";" + QString::number(event->y()) + ")";
        qDebug() << text;
        QPixmap carte(m_fichierCarte);
        int resultatPixelPointX = QVariant(QString::number(event->x())).toInt();
        int resultatPixelPointY = QVariant(QString::number(event->y())).toInt();;

        resultatPixelPointY = carte.height() + resultatPixelPointY;

        double distanceLongitude = std::fabs(m_BBOXmaxLongitude - m_BBOXminLongitude);
        double distanceLatitude = std::fabs(m_BBOXmaxLatitude - m_BBOXminLatitude);

        double coefficient_X = carte.width() / distanceLongitude;
        double coefficient_Y = carte.height() / distanceLatitude;

        double longitude = (resultatPixelPointX / coefficient_X) + m_BBOXminLongitude;
        double latitude = (resultatPixelPointY / coefficient_Y) + m_BBOXminLatitude;


        m_pointClicSouris.setX(event->x());
        m_pointClicSouris.setY(event->y());
        m_flagClic = 1;
        this->update();
        dialoginfo fenetre(this);

         int decalagePixmapX = 0, decalagePixmapY = 0;
         int pixelPointPixmapX, pixelPointPixmapY;
         int cptAPI = 0;
         listeInfoGeoObj .clear();
          for (auto listePI_API : m_listePI_API)
              for (auto elem : listePI_API )
              {
                  decalagePixmapX = listePI_API.first().pixmap.width()/2;
                  decalagePixmapY = listePI_API.first().pixmap.height();
                  resultatPixelPointX = static_cast<int> ((elem.longitude - m_BBOXminLongitude) * coefficient_X);
                  resultatPixelPointY = static_cast<int> ((elem.latitude - m_BBOXminLatitude) * coefficient_Y);

                  // inversion de l'axe verticale pixel par rapport au sens de l'axe latitude
                  resultatPixelPointY = carte.height() - resultatPixelPointY;

                  // prise en compte du hotspot du pixmap
                pixelPointPixmapX = resultatPixelPointX - decalagePixmapX;
                pixelPointPixmapY = resultatPixelPointY - decalagePixmapY;

                  if(resultatPixelPointX>=0 && resultatPixelPointX<m_largeurImage
                          && resultatPixelPointY>=0 && resultatPixelPointY<m_hauteurImage)
                  {

                  if( (event->x() >= pixelPointPixmapX) && (event->x() <= pixelPointPixmapX + elem.pixmap.width()) &&
                      (event->y() >= pixelPointPixmapY) && (event->y() <= pixelPointPixmapY + elem.pixmap.height()) )
                      {
                          listeInfoGeoObj << elem;
                          //qDebug() <<"listeInfo "<<listeInfoGeoObj.count();
                       }
                 }
             }
        fenetre.setData(longitude, latitude, listeInfoGeoObj);
        fenetre.exec();
    }
}

WidgetMap::~WidgetMap()
{
    delete m_settings;
}
