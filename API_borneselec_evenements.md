# APIs BORNES ELECTRIQUES & EVENEMENTS.

## Bornes de recharge pour véhicules électriques

**URL**

https://opendata.paris.fr/api/records/1.0/search/?dataset=bornes-de-recharge-pour-vehicules-electriques

**RAFRAICHISSEMENT**

Non communiqué 

**REQUETES**

5000 / jour 

**RESUME**

API contenant plus de 1000 bornes pour recharger un véhicule électrique en complément du service Belib', à Paris. L'API donne l'emplacement des 270 bornes de recharge du réseau Belib' et des 1127 bornes Autolib réactivées, à compter du 1er Décembre 2018 (dernier traitement le 4 décembre 2018).

**EXEMPLE**

Toutes les bornes dont l'adresse_ville (= la ville) est égale à "Paris" :
https://opendata.paris.fr/api/records/1.0/search/?dataset=bornes-de-recharge-pour-vehicules-electriques&refine.adresse_ville=Paris

Résultat renvoyé (1 seule borne pour l'exemple) : 

```
{
    "nhits": 1397,
    "parameters": {
        "dataset": [
            "bornes-de-recharge-pour-vehicules-electriques"
        ],
        "refine": {
            "adresse_ville": "Paris"
        },
        "timezone": "UTC",
        "rows": 10,
        "format": "json"
    },
    "records": [
        {
            "datasetid": "bornes-de-recharge-pour-vehicules-electriques",
            "recordid": "5a1a93bbdc940b186a391bc30078dc13f2de973f",
            "fields": {
                "objectid": 1003,
                "id_autolib": "75118-20",
                "comptage_energie": "oui",
                "communication_supervision": "néant",
                "acces_reseau": "inscription",
                "id_station": "FR*W75*PVP*0181",
                "horaires_sav": "7/7 de 7h à 22h",
                "reseau": "Bornes de recharge",
                "type_lieu": "Voirie publique",
                "tel_sav_sodetrel": "01 88 32 90 95",
                "fabricant_borne": "IER",
                "adresse_pays": "France",
                "nbre_pdc": 1,
                "id_pdc": "FR*W75*EVP*0181*0002",
                "latitude": 48.8844148,
                "paiement": "redevance annuelle",
                "type_charge": "normale",
                "type_courant_pdc": "AC mono",
                "emplacement_borne": "trottoir",
                "ref_produit": "IER 981 A01",
                "tarif_autopartage": "600 €/an",
                "type_connecteur_pdc": "prise T3",
                "adresse_ville": "Paris",
                "authentification_borne": "néant",
                "geo_shape": {
                    "type": "Point",
                    "coordinates": [
                        2.330460254845015,
                        48.884606933418155
                    ]
                },
                "nom_porteur": "Mairie de Paris",
                "puissance_pdc_kw": 3.7,
                "nom_station": "Paris/Rachel/1",
                "acces_lieu": "7/7-24/24",
                "tarif_general": "120 €/an",
                "adresse_rue": "1 avenue Rachel",
                "geo_point_2d": [
                    48.884606933418155,
                    2.330460254845015
                ],
                "longitude": 2.330546099999999,
                "adresse_cp": 75018,
                "superviseur_reseau": "Mairie de Paris",
                "abon_enedis_kw": 36,
                "nombre_places": "1"
            },
            "geometry": {
                "type": "Point",
                "coordinates": [
                    2.330460254845015,
                    48.884606933418155
                ]
            },
            "record_timestamp": "2018-12-04T09:20:21+00:00"
        },
```

**COMMENT CONSTRUIRE SA REQUETE SOUS QT**

L'appel à l'API se fait sans authentification, via un `QUrl` ainsi qu'un `QNetworkRequest` :

```
	apicalls = new QNetworkAccessManager(this);

	QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=bornes-de-recharge-pour-vehicules-electriques");

	QNetworkRequest request;
	request.setUrl(url);

	currentReply = apicalls->get(request);
```

Le retour de l'API est construit de manière simple, commençant par des tableaux `records [ ]` et en contenient d'autres à l'intérieur de chaque `record` (les `coordinates` par exemple). Pour accéder à la data, il faut transformer les `records` en `QJsonArray` après avoir correctement lu (`readAll`) le JSON renvoyé par la requête :

```
 	doc = QJsonDocument::fromJson(reply->readAll());
 	obj = doc.object();
 	arr = obj["records"].toArray();
```
`
Parcourez ensuite les data via une boucle `for` en transformant les valeurs lues en `QJsonObject` et en les affichant comme vous le souhaitez (dans l'exemple via un `qDebug`). 

```
        QJsonObject objn = val.toObject();

        qDebug() << objn["recordid"].toString();
        qDebug() << objn["fields"].toObject()["id_station"].toString();
```

Attention, certaines data sont des tableaux au sein de certains champs, il faudra alors les re-transformer en `QJsonArray` pour les lire : 

```
        qDebug() << objn["fields"].toObject()["geo_shape"].toObject()["coordinates"].toArray()[0].toDouble();
```

---------------------------------------------------------------------------------------

## Liste des événements

**URL**

https://api.predicthq.com/v1/events/

**RAFRAICHISSEMENT**

Temps réel 

**REQUETES**

10000 / mois, 100 / minute

**RESUME**

API couvrant la majorité des événements mondiaux, tels que des conférences, concerts, matchs sportifs, etc. L'API permet des recherches d'événements autour d'un endroit spécifique, utilisant un rayon exprimé en kilomètres ou mètres autour d'une longitude et latitude précisée (par exemple Paris).
Attention, l'API en version gratuite limite la requête à 10 résultats par page, pour un maximum de 2 pages requetées (20 résultats par requête). Aussi, la version gratuite ne remonte les événements que 14 jours dans le passé et limite les dates des événements futurs aux prochains 30 jours seulement. 

**EXEMPLE**

Tous les événements dans un rayon de 10km autour de Paris dont la date de début est supérieure au 11 Avril 2019 :
https://api.predicthq.com/v1/events/?country=FR&active.gte=2019-04-11&within=10km@48.85341,2.3488

Résultat renvoyé (1 seul événement pour l'exemple) : 

```
{
    "count": 20,
    "overflow": true,
    "next": "https://api.predicthq.com/v1/events/active.gte=2019-04-11&country=FR&offset=10&within=10km%4048.85341%2C2.3488",
    "previous": null,
    "results": [
        {
            "relevance": 1,
            "id": "9vXS3ckGkT24Vsw6xe",
            "title": "Le Beau Festival",
            "description": "",
            "category": "festivals",
            "labels": [
                "festival",
                "music"
            ],
            "rank": 47,
            "local_rank": 49,
            "duration": 172799,
            "start": "2019-05-16T22:00:00Z",
            "end": "2019-05-18T21:59:59Z",
            "updated": "2019-03-06T05:43:28Z",
            "first_seen": "2019-03-06T05:43:11Z",
            "timezone": "Europe/Paris",
            "location": [
                2.394431,
                48.889095
            ],
            "scope": "locality",
            "country": "FR",
            "place_hierarchies": [
                [
                    "6295630",
                    "6255148",
                    "3017382",
                    "3012874",
                    "2975246",
                    "6457371",
                    "6452608",
                    "3032179"
                ],
                [
                    "6295630",
                    "6255148",
                    "3017382",
                    "3012874",
                    "2975246",
                    "6457371",
                    "6614030",
                    "3002499"
                ]
            ],
            "state": "active"
        }
```

**COMMENT CONSTRUIRE SA REQUETE SOUS QT**

Les requêtes requièrent une authentification fournie par PredictHQ (`$Client_ID`:`$Client_Secret`). Il s'agit d'un `Bearer Token` à passer en `Header` de la requète. Pour cela, il faut utiliser la fonction `setRawHeader(QByteArray("VOTRE MODE D'AUTH"), QByteArray("VOTRE TYPE DE TOKEN ET LE TOKEN"))`, accompagnée d'un `QUrl` contenant votre requête et ses paramètres : 

```
	apicalls = new QNetworkAccessManager(this);

	QUrl url("https://api.predicthq.com/v1/events/?country=FR&active.gte=2019-04-16&within=10km@48.85341,2.3488");

	QNetworkRequest request;
	request.setUrl(url);
	request.setRawHeader(QByteArray("Authorization"), QByteArray("VOTRE BEARER TOKEN"));

	currentReply = apicalls->get(request);
```

Le retour de l'API est construit de manière simple, commençant par des tableaux `results [ ]` et en contenient d'autres à l'intérieur de chaque `result` (les `labels` ou `location` par exemple). Pour accéder à la data, il faut transformer les `results` en `QJsonArray` après avoir correctement lu (`readAll`) le JSON renvoyé par la requête :

```
 	doc = QJsonDocument::fromJson(reply->readAll());
 	obj = doc.object();
 	arr = obj["results"].toArray();
```

Parcourez ensuite les data via une boucle `for` en transformant les valeurs lues en `QJsonObject` et en les affichant comme vous le souhaitez (dans l'exemple via un `qDebug`). 

```
        QJsonObject objn = val.toObject();

        qDebug() << objn["title"].toString();
```

Attention, certaines data sont des tableaux au sein de certains champs, il faudra alors les re-transformer en `QJsonArray` pour les lire : 

```
        qDebug() << objn["labels"].toArray()[0].toString();
```

