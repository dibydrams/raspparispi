# **Module RATP**

## URLS

Requêtes Unitaires : https://api-lab-trone-stif.opendata.stif.info/pages/api-test-temps-reel/

Requête Globale : https://api-lab-trall-stif.opendata.stif.info/explore/dataset/tr-globale-stif/information/

## Nombre de Requetes Free / Jour

Unitaires : 200 000.

Global : 1 000.

## Résumé

Cette api permet de connaitre les prochains départs des lignes de bus, métro ou trains
à une station précise.

Les temps d'attentes sont exprimés en minutes.

**Taux de Raffraîchissement**

La liste des données disponibles sera mise à jour toutes les 2 semaines.

**Les horaires**

• Les horaires fournis dans les services StopMonitoring, GeneralMessage et EstimatedTimeTable
sont représentés selon la norme internationale ISO 8601 et sont exprimés en heure UTC (Temps
universel Coordonné).

• En ce qui concerne les données issues du canal Vianavigo, les horaires de passages à l’arrêt sont
fournis en temps d’attente exprimés en minutes.

**Les perturbations**

• Chaque perturbation est localisée sur des lignes ou des arrêts avec des identifiants issus des
référentiels.

• Pour les messages de perturbations, trois types de textes peuvent être fournis.

• Un texte brut (textOnly) qui est obligatoire et qui sera toujours renseigné.

• Deux autres textes facultatifs qui ne seront pas forcément renseignés.

• Un message court (shortMessage).

• Un message long qui peut posséder des éléments de mise en forme (longMessage).

### Format de retour

**Unitaires**

Le résultat est de la forme :

"vehicleName": "<Code mission de la circulation, retourné si existe (RATP/SNCF)>",

"lineDirection": "<direction de la ligne>",

"sens": "<Sens de la ligne : 1 | -1, retourné si disponible>",

"code": "<indique s’il s’agit d’un temps ou d’un message : duration | message>",

"time": "<temps restants pour les prochains départs en minutes, retourné si code=duration>",

"schedule": "<message, retourné si code=message ou si le service tiers temps réel renvoie un message en plus d’un temps>"

**Globale**
???


### Code D'erreur

**Unitaires**

Message d’erreur | Signification du message d’erreur renvoyé
--- | ---
"err_code": "POINT_IS_MANDATORY" | Aucun identifiant d’arrêt n’est renseigné
"err_code": "LINE_IS_MANDATORY" | L’identifiant de la ligne n’est pas renseigné
"err_code": "NO_REALTIME_FOR_LINE" | La ligne ne possède pas de temps réel
"err_code": "STOP_NOT_FOUND" | L’identifiant de l’arrêt (ou de la zone d’arrêt) n’est pas valide
"err_code": "LINE_NOT_FOUND" | L’identifiant de la ligne n’est pas valide
"err_code": "NO_REALTIME_SCHEDULES_FOUND" | La liste des prochains départs n’a pas pu être récupérée
"err_code": "REALTIME_SERVICE_ERROR | Le service tiers de RATP est indisponible

**Globale**
???

