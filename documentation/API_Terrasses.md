
#Etalages et Terrasses





	
##Description des données.
Ce jeu de données recense les étalages et terrasses à Paris. 
L'installation des étalages et terrasses sur la voie publique ainsi que des contre-étalages et contre-terrasses, des commerces accessoires aux terrasses et des dépôts de matériel ou objets divers devant les boutiques sont soumises à autorisation.
Pour ce projet, on ce limite aux terrasses ouvertes et fermeés sur Paris. L'API nous donne 13999 enregistrements.


###Adresse de l'API

	https://opendata.paris.fr/explore/dataset/etalages-et-terrasses/information/?disjunctive.libelle_type&disjunctive.red_profession&refine.libelle_type=TERRASSE+OUVERTE&refine.libelle_type=TERRASSE+FERMEE

### 1. Les données d'enter

- Libelle_type_objet : terrasse ouverte, terrasse fermée,

- Red_profession : c'est le type d'activités

- Adresse

- Largeur de l’emprise autorisée. 

- Longueur de l’emprise autorisée.

- Raison sociale du bénéficiaire

- Type_lieu* 

###2. Exemple de requette

{"nhits": 0, "parameters": {"dataset": ["etalages-et-terrasses"], "refine": {"libelle_type": ["TERRASSE OUVERTE", "TERRASSE FERMEE"]}, "timezone": "UTC", "rows": 10, "format": "json", "facet": ["libelle_type", "red_profession", "type_lieu1", "type_lieu2", "lateralite", "longueur", "largeurmin", "largeurmax", "date_periode"]}, "records": []}

{
    • "nhits":0,
    • "parameters":
      {
        ◦ "dataset":
          [
            ▪ "etalages-et-terrasses"
          ]
          ,
        ◦ "refine":
          {
            ▪ "libelle_type":
              [
                • "TERRASSE OUVERTE",
                • "TERRASSE FERMEE"
              ]
          }
          ,
        ◦ "timezone":"UTC",
        ◦ "rows":10,
        ◦ "format":"json",
        ◦ "facet":
          [
            ▪ "libelle_type",
            ▪ "red_profession",
            ▪ "type_lieu1",
            ▪ "type_lieu2",
            ▪ "lateralite",
            ▪ "longueur",
            ▪ "largeurmin",
            ▪ "largeurmax",
            ▪ "date_periode"
          ]
      }
      ,
    • "records":
      [
      ]
}


	*TYPE_LIEU :

	A : Salle d'auditions, salle de conférences, salle de réunions ; 
	B : Salle réservée aux associations, salle de quartier (ou assimilée) ; 
	C : Salle de projection, salle de spectacles (y compris les cirques non forains) ; 
	D : Cabarets ; 
	E : Salle polyvalente à dominante sportive dont la superficie unitaire est supérieure ou égale à 1200 mètres carrés, ou dont la hauteur sous plafond est inférieure à 6,50 mètres ; 
	F : Autre salle polyvalente non visée ci-dessus et non visée au type X ; 
	G : Salles multimédia. 
