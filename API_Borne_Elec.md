# Bornes pour recharger votre véhicule électrique !

### #1 OpenData Paris - Bornes de recharge pour véhicules électriques 

OpenData Paris propose une API pour localiser les emplacements des bornes de recharge pour véhicules électriques du réseau Belib' et Autolib. Son utilisation est entièrement **gratuite**, sans authentification mais limitée à **5000 requêtes** par jour. Aucune information n'est disponible sur le taux de raffraîchissement et la dernière mise à jour remonte au 4 décembre 2018.

> Documentation de l'API
```
https://opendata.paris.fr/explore/dataset/bornes-de-recharge-pour-vehicules-electriques/
```

#### Les choses à savoir
- Recharger son véhicule électrique sur les anciennes bornes Autolib' est maintenant possible depuis le 3 décembre 2018. *( Présent dans les données de l'API )*
- L'utilisation des bornes est conditionnée par l'achat d'une carte spécifique "Recharge électrique".  *( Les prix sont présents dans les données de l'API )*

#### Utilisation de l'API 
> Adresse pour les requêtes
```
https://opendata.paris.fr/api/records/1.0/search/?dataset=bornes-de-recharge-pour-vehicules-electriques
```

#### Filtrer les données

Vous pouvez filtrer les données de l'API en GET en y ajoutant des critères dans l'adresse.

**1 ) Exemple d'une requête**  

L'exemple permet de d'affiner la recherche avec le nom du **reseau Belib'** sous la forme ( clé => valeur ) ce qui donne *refine.réseau=Belib'*. Puis un autre critère est passé en paramètre pour trier les résultats avec l'ID de la borne de recharge. On lui passe la clé **objectifid** qui a pour valeur un entier. Par défaut, le tri se fera par ordre décroissant *( l'ajout d'un "-" devant objectid permet l'affichage de façon croissante )*.

```
&refine.reseau=Belib'&sort=objectid
```


**2 ) Les paramètres**  

-  **dataset**  : Ne doit pas être modifié. Il sert à pointer sur le jeu de données "bornes-de-recharge-pour-vehicules-electriques"
-  **q** : Permet de chercher une occurence. Ex : *q=400* va chercher un nombre 400 dans toutes les valeurs.
-  **rows** : Permet de définir le nombre de résultats. Par défaut, il est de 10. Vous pouvez augmenter ce nombre mais attention aux performances.
-  **start** : Spécifier l'index du début de la recherche. *(Pour pagination)*
-  **refine.** : Il permet d'affiner la recherche avec une clé et une valeur. *( Voir exemple plus haut )*
-  **exclude** : Le contraire de *refine*. Vous pouvez exclure des données. 
-  **sort** : Trier les données par ordre croissant ou décroissant avec un champ.
-  **facet** : Permet d'inclure une recherche supplémentaire avec notre requête. Ex : *reseau* va afficher un facet_groups avec tous les résultats de reseau ( Bornes de recharge et Belib'). Voir plus bas.
-  **geo.distance** : 
-  **timezone** : La zone permet d'afficher la date et l'heure dans le bon format. Ex : Europe/Paris

#### Les données de retour

L'API retourne du JSON avec des tableaux.

- **records** : Affiche le résultat de ma requête pour les bornes

```
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

  - **facet_groups** : Affiche le résultat de la requête du **facet** pour le **reseau**. 

```
"facet_groups": [
    {
      "name": "reseau",
      "facets": [
        {
          "name": "Bornes de recharge",
          "path": "Bornes de recharge",
          "count": 1127,
          "state": "displayed"
        },
        {
          "name": "Belib'",
          "path": "Belib'",
          "count": 270,
          "state": "displayed"
        }
      ]
    }
  ]

```

On retrouve bien le réseau avec nos deux élements. Celle de la société Belib' et Bornes de recharge (inclus Autolib).


