# Application affichant la liste des fontaines à Paris
============================================

## Resumé:
------------------------
- Avec cette application, on peut avoir la liste des fontaines autour d'une adresse, il peut y avoir des fontaines à boire ou juste des jeux d'eau.
- Avec notre projet, nous utilisons l'adresse 6 rue Rougemont Paris 75009 comme adresse d'installation de l'application avec les coordonnées GPS (48.8716 , 2.34599).
- Cette application propose quatres types de fontaines selon les données disponibles sur le site internet de ParisData.gouv dont le lien[opendata.paris.fr](https://opendata.paris.fr/) . Ce site internet propose des données avec application gratuite.
- Pour avoir la liste des fontaines au alentours de notre adresse, on utilise la requette suivante [[dans une zone de 600m autours de 6 rue Rougemont](https://opendata.paris.fr/api/records/1.0/search/?dataset=fontaines-a-boire&facet=arro&facet=modele&facet=a_boire&geofilter.distance=48.8716+%2C+2.34599%2C+600&timezone=Europe%2FParis&rows=-1) ].

- Pour voir les résultats d'une autres adresse, on le change juste dans la requette l'adresse GPS et on aura les résultats.

