# 
# Application affichant les kiosques journaux magazines presses à Paris
====================================


## Resumé:
______________
 - Cette application permet d'afficher des adresses de kiosque ouvert la plus proche d'une adresse à Paris.
 - Avec notre projet, nous utilisons l'adresse 6 rue Rougemont Paris 75009  comme adresse d'installation de l'application avec les coordonnées GPS(48.8716 , 2.34599).
 - On utilise surtout avec cette application le lien de données sur le site internet de ParisData.gouv selon le lien [opendata.paris.fr](https://opendata.paris.fr/) qui propose des listes de données avec application gratuite.
 - Pour avoir la liste des kiosques au alentours de notre adresse, on utilise la requette suivante [dans une zone de 600m autours de 6 rue Rougemont](https://opendata.paris.fr/api/records/1.0/search/?dataset=liste_des_kiosques_presse_a_paris&facet=code_postal&facet=statut&geofilter.distance=48.8716%2C2.34599%2C600&timezone=Europe%2FParis&rows=-1) 
 - Pour voir les résultats d'une autres adresse, on le change juste dans la requette l'adresse GPS et on aura les résultats.


