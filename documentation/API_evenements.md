# APIs RECOLTE DES EVENEMENTS.

## Liste des événements

**URL DU SERVICE API**

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

