/*
 * ##  CLASSE ABSTRAITE : DESCRIPTION  ##
 *
 * La classe abstraite Abstract_API permet d'identifier votre set de données via une énumération prévue à cet effet et qui peut être complétée si nécessaire.
 * La classe permet de récupérer un format standard des coordonées GPS des points d'intérêts à afficher sur la map, tels que la longitude et latitude.
 * La classe contient un signal permettant d'identifier la fin du traitement de vos données par vos APIs ou base de données.
 *
 *
 * # CONTENU DE LA CLASSE #
 *
 * ---- 2 méthodes virtuelles pures :
 * ---------- a. getPixmap() servant à récupérer l'icône pour votre bouton du bandeau inférieur
 * ---------- b. getID() retournant  votre identifiant parmi les champs de l'énumération
 *
 * ---- 1 slot virtuel pur :
 * ---------- a. getInfo() permettant, depuis votre classe, de lancer vos méthodes de traitement de data
 *
 * ---- 1 méthode publique :
 * ---------- a. debug(QList) qui prend un QList ou que vous pouvez customiser afin de débugger vos structures / données
 *
 * ---- 1 signal public :
 * ---------- a. callFinished(QList<GeoObj>) qui prend une liste de structures de <GeoObj> (voir détail de la structure) et qui permettra, dans votre classe, de notifier la fin du traitement de vos données.
 * ---------- Par la suite, ce signal permettra d'être connecté à une méthode du MainWindow qui renverra la liste complète de <GeoObj> que l'on pourra afficher sur la map
 *
 *
 * Si besoin, la classe apievenementsmv.h /.cpp permet de voir un type d'utilisation des méthodes virtuelles pures.
 * Cependant, il s'agit seulement d'UN exemple adapté à un type d'API et JSON bien spécifique. */


#ifndef ABSTRACT_API_H
#define ABSTRACT_API_H

#include <QApplication>
#include <QObject>
#include <QPixmap>
#include <QDebug>

class CustomButton;

class Abstract_API : public QObject
{
    Q_OBJECT

public:
    explicit Abstract_API(QObject *parent = nullptr );

    /* Enumération servant d'identification
     * Vous pouvez modifier et/ou rajouter des identifiants si nécessaires, en majuscules
     * Ne pas supprimer d'identifiants utilisés */

    enum API_index {
        EVENEMENTS ,
        RATP ,
        TERRASSES ,
        VELIB ,
        PARKING_PUBLIC ,
        PARKING_PRIVE ,
        BORNES_ELEC ,
        METEO ,
        ESPACES_VERTS ,
        TOILETTES,
        KIOSQUES ,
        PHARMACIES,
        BORNES_WIFI,
        CRUES,
        ANIMATIONS,
        THEATRE,
        FONTAINES,
        TRADUCTION,
        RESET,
    };



    /* Structure permettant de formatter les résultats (coordonnées, icônes, ID)
     * Les longitudes et latitudes doivent IMPERATIVEMENT être exprimées en type Double
     * L'ID correspond à un numéro associé aux catégories de l'énumération (EVENEMENTS = 0, RATP = 1, TERRASSES = 2, etc.) */
    struct  GeoObj {
        double longitude;
        double latitude;
        QPixmap pixmap;
    };

    /* Structure permettant de récupérer la long, la lat et l'id, lors du clic sur l'icone*/
    struct ClickedGeoObj {
        double longitude;
        double latitude;
        int id;
    };

    // Méthodes virtuelles pures + explications
    virtual QPixmap getPixmap() = 0;
    virtual API_index getId() = 0;

    // Public slot sous forme de méthode virtuelle pure
public slots:
    virtual void getInfo() = 0;

    // Aide au déboggage
public:
    void debug(QList<GeoObj> list);
    void debugId(QList<ClickedGeoObj> listclickedgeoobj);

    // Signal de fin de process des data
signals:
    void callFinished(QList<Abstract_API::GeoObj> list, Abstract_API::API_index id);
    void callEmpty(QList<GeoObj> list);
};

#endif // ABSTRACT_API_H

