# API sanisettes

## Recherche des Sanisettes alentours

### URLs

Le site de l'api est Paris Data.
Son url est : "https://opendata.paris.fr/"

L'url de l'IHM de l'API est : "https://opendata.paris.fr/api/v1/console/datasets/1.0/search/"

L'url de la partie IHM de l'api ciblant les sanisettes est : "https://opendata.paris.fr/explore/dataset/sanisettesparis/api/"

### L'API

L'API de Paris Data s'appuie sur L'API Opendatsoft ( "https://www.opendatasoft.fr/" ).

Le paramètre "dataset" permet déterminer l'objet de la recherche.
Le paramètre "lang" permet de déterminer la lang du texte.
Le paramètre "rows" permet de déterminer le nombre de résultats désirés.
Le paramètre "facet" permet de déterminer diverses informations désirées en retour.
Le paramètre "geofilter.distance" permet de déterminer un point de départ avec un périmètre de recherche pour la recherche.

### Exemples

Une requêtes répertoriant l'ensemble des sanisettes :
"https://opendata.paris.fr/api/records/1.0/search/?dataset=sanisettesparis&facet=arrondissement&facet=horaires_ouverture"

Une requêtes avec point WGS84 et perimetre:
"https://opendata.paris.fr/api/records/1.0/search/?dataset=sanisettesparis&facet=arrondissement&facet=horaires_ouverture&geofilter.distance=48.8716%2C2.345990000000029%2C1000"


