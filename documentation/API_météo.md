# API Météo

## Météo –  Indice Uv 


### URL : 
- https://openweathermap.org/price
- https://www.infoclimat.fr/api-previsions-meteo.html?id=2988507&cntry=FR


### Temps de rafraîchissement :
Openweather : Data update < 2 heures et Map update < 3heures

### Nombre d’entrée gratuite :
Openweather : 60 requêtes maximum par minutes soit 86400 requêtes par jour.
Infoclimat : Cette API est limitée à un usage raisonnable et non commercial. Est considéré comme raisonnable un usage de moins de 5.000 requêtes en 24 heures et de moins d'une requête par seconde, pour l'ensemble des API de prévisions.

### Résumé : 
Openweather : Pareil que Infoclimat + indice UV + précipitations (pluie...)

Infoclimat :Données de prévisions météo à 7 jours en JSON, XML, CSV.
Cette API donne les informations suivantes : 
- Températures en Kelvin à 2 mètres du sol
- Humidité relative
- Pression au niveau de la mer
- Force du vent moyen
- Direction du vent moyen
- Vitesse du vent verticale




## Pollution Air – Journée sans Voitures

### URL : 
- https://www.airparif.asso.fr/rss/index
- https://www.data.gouv.fr/fr/organizations/airparif-1/

### Temps de rafraîchissement :
Journaliers

### Résumé : 
Plusieurs API sont disponibles : la première donne accès à l’indice de qualité de l’air du jour et du lendemain, la deuxième aux informations en cas d’alerte de pollution et la troisième aux données spatialisées issues des cartes hautes définition de la région en temps réel. 
Cette dernière API est encore en phase de tests. 
Concentrations moyennes journalières issues du réseau fixe des principaux polluants réglementés dans l'air sur la région Île-de-France : dioxyde de soufre SO2, monoxyde d'azote NO et dioxyde d'azote NO2, particules en suspension PM10, particules en suspension PM2.5, ozone O3, benzène C6H6, monoxyde de carbone CO. 
Toutes les données fournies sont en μg/m³ (microgramme par mètre cube) sauf CO (mg/m³).


## UV INDEX

### API call:
http://api.openweathermap.org/data/2.5/uvi/forecast?appid={appid}&lat={lat}&lon={lon}&cnt={cnt})

### Parameters:
appid - personal API key
lat, lon - coordinates of the location of your interest (latitude/longitude)
cnt - number of returned days

### Examples of API calls:
api.openweathermap.org/data/2.5/uvi/forecast?lat=37.75&lon=-122.37
http://api.openweathermap.org/data/2.5/uvi?appid={appid}&lat={lat}&lon={lon} 




