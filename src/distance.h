#ifndef DISTANCE_H
#define DISTANCE_H

/**
* \author Jean-Sébastien
* \date 6 mai 2019
* \version   1.0
*
* \class distance
* \brief  Class appelant l'API tomtom pour fournir la distance entre deux points géographiques
* ainsi que d'autre informations complémentaires relatives aux trajets
* \details Cette class a un constructeur surchargé permettant de faire appelle à l'API
* avec des coordonnées de type string ou double.
*/

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QBitArray>
#include <QEventLoop>
#include <QDebug>

/**
 * @brief The distance class
 * @details La classe contient les propriétés suivantes:
 * distanceInMeters (int)       : distance en mètres
 * timetravel (int)             : temps de trajet en secondes
 * delay (int)                  : retard en secondes
 * timetravelWithTraffic (int)  : temps de trajet en tenant compte du traffic, en secondes
 * arrival (Qstring)            : heure d'arrivée Qstring format DateTime
 *
 * La classe possède aussi un SLOT dataReading(), qui sera appellée
 *  à la reception du SIGNAL finished() d'un reply
 *
 * La classe possède un SIGNAL readed() pour signaler que les données ont été lues.
 */
class distance : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief constructor
     * @param parent -> ponter sur QObject
     * @details constructeur simple et vide qui ne fera pas appel à l'API de lui même
     * Il faudra donc après optention de l'objet lui demander d'effectuer une requête avec la fonction "setRequest()"
     */
    explicit distance(QObject *parent = nullptr);

    /**
     * @brief distance
     * @param longitudeDest de type QString
     * @param latitudeDest  de type QString
     * @param parent
     * @details surcharge du constructeur; Par default le point de départ est 6 rue rougemont et le mode de deplacement est piéton (pedestrian).
     * Avec ce constructeur, la requête à l'API TomTom est immédiatement crée et envoyée.
     */
    explicit distance(QString longitudeDest, QString latitudeDest, QObject *parent = nullptr);

    /**
     * @brief distance
     * @param longitudeDest de type QString
     * @param latitudeDest de type QString
     * @param modeDeTransport de type QString
     * @param parent -> pointer sur QObject
     * @details surcharge du constructeur permettant de définir un mode de transport
     * les différents modes de transports sont : " car "(voiture; par default) , " pedestrian " (piéton), " bicycle " (vélo) , " motorcycle " (deux roues motorisées),
     * " van " , " bus ", " taxi ", " truck ".
     * Pour que cela fonctionne correctement il faut bien inscrire l'un des moyen de transport énnoncé en anglais entre guillemets précédemment.
     */
    explicit distance(QString longitudeDest, QString latitudeDest, QString modeDeTransport, QObject *parent = nullptr);

    /**
     * @brief distance
     * @param longitudeDest de type COLOR_YELLOW double
     * @param latitudeDest de type COLOR_YELLOW double
     * @param parent de type COLOR_OLIVE QObject
     * @details Surcharge du constructeur permettant de mettre des doubles pour renseigner la longitude et la latitude de detination
     */
    explicit distance(double longitudeDest, double latitudeDest, QObject *parent = nullptr);

    /**
     * @brief distance
     * @param longitudeDest de type double
     * @param latitudeDest de type double
     * @param modeDeTransport de type QString
     * @param parent de type QObject
     * @details Surcharge du constructeur permettant de mettre des doubles pour renseigner la longitude et la latitude de detination
     */
    explicit distance(double longitudeDest, double latitudeDest, QString modeDeTransport, QObject *parent = nullptr);


    /**
     * @brief setRequest
     * @param longitudeDest de type QString
     * @param latitudeDest de type QString
     * @return url de request de type QString
     */
    QString setRequest(QString longitudeDest, QString latitudeDest);

    /**
     * @brief setRequest
     * @param longitudeDest
     * @param latitudeDest
     * @param modeDeTransport
     * @details surcharge de la fonction setRequest(); permet de renseigner le mode de transport
     * @return url de request de type QString
     */
    QString setRequest(QString longitudeDest, QString latitudeDest, QString modeDeTransport);

    /**
     * @brief setRequest
     * @param longitudeDest de type double
     * @param latitudeDest de type double
     * @return url de request de type QString
     */
    QString setRequest(double longitudeDest, double latitudeDest);

    /**
     * @brief setRequest
     * @param longitudeDest
     * @param latitudeDest
     * @param modeDeTransport
     * @return url de request de type QString
     */
    QString setRequest(double longitudeDest, double latitudeDest, QString modeDeTransport);

    int getDistanceInMeters() const;
    void setDistanceInMeters(int value);

    int getTimetravel() const;
    void setTimetravel(int value);

    int getDelay() const;
    void setDelay(int value);

    int getTimetravelWithTraffic() const;
    void setTimetravelWithTraffic(int value);

    void readJson();

    QString getArrival() const;
    void setArrival(const QString &value);

    virtual ~distance();

private:
    QNetworkAccessManager * manager;
    QNetworkRequest request;
    QNetworkReply * reply;
    QHash <QString, QVariant> distance_hash;
    QEventLoop loop;

    int distanceInMeters;
    int timetravel;
    int delay;
    int timetravelWithTraffic;
    QString arrival;

public slots:
    void dataReading();

signals:
    void readed();

};

#endif // DISTANCE_H
