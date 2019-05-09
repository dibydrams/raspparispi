# Animations sur Paris

### #1 OpenData Paris - API Que faire à Paris

OpenData Paris propose une API pour localiser tous les événements qui se déroulent sur Paris. Cette API permet de visualiser toutes les catégories suivantes : les événements, les concerts, les musées, les animations, les festivals, les spectacles et les expositions. Son utilisation est entièrement **gratuite**, sans authentification mais limitée à **5000 requêtes** par jour sur la version 2. Le taux de rafraîchissement est quotidien et la dernière mise à jour remonte au 7 Mai 2019.

> Documentation de l'API
```
https://opendata.paris.fr/explore/dataset/que-faire-a-paris-/
```

#### Les choses à savoir
- La requête ne récupère que la catégorie "Animations" pour éviter des doublons avec l'API des événements de Michael.
- Un filtrage est effectué sur la ville de Paris et sur les événements qui ont lieu en ce moment.

#### Utilisation de l'API
> Adresse pour les requêtes
```
https://opendata.paris.fr/api/records/1.0/search/?dataset=que-faire-a-paris-
```

**2 ) Les données récupérées pour l'affichage**  

-  **title**  : Le titre de l'animation.
-  **addresse_street** : Le numéro et la rue de l'animation.
-  **addresse_zipcode** : Le code postal sur Paris.
-  **lead_text** : Un descriptif assez court.
-  **description** : Un descriptif détaillé sur l'animation en cours.
-  **transport** : Les lignes de métro et de bus pour accéder au lieu.
-  **price_detail** : Gratuit ou payant avec le prix en euro.
-  **deaf** : Retourne la valeur 1 si accessible pour les sourds.
-  **blind** : Retourne la valeur 1 si accessible pour les malvoyants.
-  **date_start** : La date de début au format (YYYY/MM/DD).
-  **date_end** : La date de fin dans le même format.
-  **cover_url** : Permet d'obtenir l'image pour illustrer l'animation.
-  **contact_email** : L'adresse email pour les questions ou les réservations.
-  **contact_phone** : Le numéro de téléphone de contact.
-  **contact_facebook** : Le lien vers la page facebook.
