#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Abstract_API.h"
#include "dialogmeteo.h"
#include "ui_dialogmeteo.h"
#include "apimeteo.h"
#include "apiterrasses.h"
#include "apiratp_station.h"

#include <QHBoxLayout>


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

    // ##   INITIATION DE CHAQUE BOUTON CI-DESSOUS  ##
    /* Chaque type de data doit initier son bouton sur l'interface en se basant sur du bouton principal : ButtonEv (le premier de la liste)
     *  Ne pas changer le code du premier bouton */

    ptr = new ApiMeteo;
    CustomButton *buttonMeteo = new CustomButton(ptr, this);
    ui->horizontalLayout->addWidget(buttonMeteo);
    buttonMeteo->setCheckable(false);
    connect(buttonMeteo, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(buttonMeteo, SIGNAL(clicked()), this, SLOT(dialog()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>)));

    ptr = new ApiEvenementsMV;
    CustomButton *buttonEv = new CustomButton(ptr, this);
    ui->horizontalLayout->addWidget(buttonEv);
    connect(buttonEv, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>)));

    ptr = new pharmapi;
    CustomButton *pharmButton = new CustomButton(ptr, this);
    ui->horizontalLayout->addWidget(pharmButton);
    connect(buttonEv, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>)));

    ptr = new ApiBornes_Elec;
    CustomButton *bornesElecBtn = new CustomButton(ptr, this);
    ui->horizontalLayout->addWidget(bornesElecBtn);
    connect(bornesElecBtn, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>)));

    ptr = new ApiQueFaire;
    CustomButton *QueFaire_btn = new CustomButton(ptr, this);
    ui->horizontalLayout->addWidget(QueFaire_btn);
    connect(QueFaire_btn, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>)));

    ptr = new ApiTerrasses;
    CustomButton *terrassesBtn = new CustomButton(ptr, this);
    ui->horizontalLayout->addWidget(terrassesBtn);
    connect(terrassesBtn, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>)));

    ptr = new sanisette;
    CustomButton *buttonToilette = new CustomButton(ptr, this);
    ui->horizontalLayout->addWidget(buttonToilette);
    connect(buttonToilette, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>))); // 6

    ptr = new ApiRatp_Global;
    CustomButton *buttonRatpGlobal = new CustomButton (ptr, this);
    ui->horizontalLayout->addWidget(buttonRatpGlobal);
    connect(buttonRatpGlobal, SIGNAL(clicked()), ptr, SLOT(getInfo()));
    connect(ptr, SIGNAL(callFinished(QList<Abstract_API::GeoObj>, API_index)), this, SLOT(dataReceived(QList<Abstract_API::GeoObj>)));
}


/* ##   FONCTION EN COURS DE CONSTRUCTION : dataReceived(QList)  ##
 *
 * Explications : Cette fonction va renvoyer la liste finale complète de GeoObj afin de les afficher sur la map.
 * Il ne devrait pas être nécessaire de modifier cette fonction. Elle sera utilisée pour positionner les points d'intérêts sur la map.
 * Utiliser sous forme de qDebug en attendant. */

void MainWindow::dataReceived(QList<Abstract_API::GeoObj> list)
{
    ui->widget->m_listePI = list;
    this->update();
}

void MainWindow::dialog()
{
    Dialog fenetre;
    fenetre.exec();
}
