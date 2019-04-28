#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Abstract_API.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  
    initButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}


/* ##   FONCTION COMMUNE : initButtons()  ##
 *
 * Fonction permettant d'initier les boutons sur l'interface.
 * Etapes précises à suivre pour la création de chacun des boutons.
 *
 *
 * -------------------- ETAPES A SUIVRE --------------------
 * ---- 1. Initiation du pointeur sur votre classe gérant vos datas
 * ---- 2. Création du bouton. Choisir un nom en rapport avec vos datas (ex: buttonMetro, buttonVelib)
 * ---- 3. Ajout du bouton au sein de l'interface principale
 * ---- 4. Connection du clic avec la fonction permettant de lancer la récupération des datas
 * ---- 5. Ajout du bouton à la liste des boutons (cela permet de les gérer tous en même temps par la suite)
 * ---- 6. Une fois le signal de traitement des data récupéré, redirection vers la méthode contenant les datas prêtes à être affichées
 *
 * FORMAT : Les boutons auront tous le même format standardisé. Il n'est donc pas nécessaire que vous appliquiez votre propre design à ceux-ci, il sera global.
 * BONUS : Si vous n'avez pas de localisations à afficher (lat/long) sur la map, vous pouvez connecter votre bouton directement à votre QDialog ici (ex: Météo) */

void MainWindow::initButtons()
{
    Abstract_API *ptr ; // Pointeur sur classe mère, ne pas changer.

    // ##   INITIATION DU BOUTON NUMERO 1 : EVENEMENTS (Ne pas changer ce code)   ##

    ptr = new ApiEvenementsMV; // 1
    CustomButton *buttonEv = new CustomButton(ptr, this); // 2
    ui->horizontalLayout->addWidget(buttonEv); // 3
    connect(buttonEv, SIGNAL(clicked()), ptr, SLOT(getInfo())); // 4
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>))); // 6

    ptr = new pharmapi; // 1
    CustomButton *pharmButton = new CustomButton(ptr, this); // 2
    ui->horizontalLayout->addWidget(pharmButton); // 3
    connect(buttonEv, SIGNAL(clicked()), ptr, SLOT(getInfo())); // 4
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>))); // 6

    ptr = new ApiBornes_Elec;
    CustomButton *bornesElecBtn = new CustomButton(ptr, this);
    ui->horizontalLayout->addWidget(bornesElecBtn);
    connect(bornesElecBtn, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>)));

    ptr = new ApiQueFaire;
    CustomButton *QueFaire_btn = new CustomButton(ptr, this);
    ui->horizontalLayout->addWidget(QueFaire_btn);
    connect(QueFaire_btn, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>)));

    // TEST DIALOG
    // connect(buttonEv, SIGNAL(clicked)), , SLOT()));

    /* Chaque type de data doit initier son bouton sur l'interface en se basant sur du bouton principal : ButtonEv (le premier de la liste)
     *  Ne pas changer le code du premier bouton
     *
     * ##   INITIATION DU BOUTON NUMERO 2 : $VOTRE_DATASET   ##
     *
     * -----> Votre code de création de bouton ici.
     *
     * ##   INITIATION DU BOUTON NUMERO 3 : $VOTRE_DATASET   ##
     *
     * -----> Votre code de création de bouton ici. */
}


/* ##   FONCTION EN COURS DE CONSTRUCTION : dataReceived(QList)  ##
 *
 * Explications : Cette fonction va renvoyer la liste finale complète de GeoObj afin de les afficher sur la map.
 * Il ne devrait pas être nécessaire de modifier cette fonction. Elle sera utilisée pour positionner les points d'intérêts sur la map.
 * Utiliser sous forme de qDebug en attendant. */

void MainWindow::dataReceived(QList<Abstract_API::GeoObj> list)
{
    for (auto i : list) {
        qDebug() << i.longitude;
        qDebug() << i.latitude;
        qDebug() << i.pixmap;
        qDebug() << i.id;
    }
}
