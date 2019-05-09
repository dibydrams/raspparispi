#include "dialogvigicrues.h"
#include "ui_dialogvigicrues.h"

DialogVigicrues::DialogVigicrues(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVigicrues)
{
    ui->setupUi(this);

    // Ajout graph hauteur en fonction du temps
    ui->widgetGraph->addGraph(ui->widgetGraph->xAxis, ui->widgetGraph->yAxis);
    ui->widgetGraph->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->widgetGraph->graph(0)->setPen(QPen(Qt::black));

    // Ajout graph debit en fonction du temps
    ui->widgetGraph->addGraph(ui->widgetGraph->xAxis, ui->widgetGraph->yAxis2);
    ui->widgetGraph->graph(1)->setLineStyle((QCPGraph::lsLine));
    ui->widgetGraph->graph(1)->setPen(QPen(Qt::red));

    // Titre du Graph
    QCPTextElement *title = new QCPTextElement(ui->widgetGraph);
    title->setText("Hauteurs et débits des dernières 24h");
    title->setFont(QFont("sans",12, QFont::Bold));
    ui->widgetGraph->plotLayout()->insertRow(0);
    ui->widgetGraph->plotLayout()->addElement(0,0, title);

    //Ajout date
    //ui->labelDate->setText((QDateTime::currentDateTime().toString("dddd dd MMMM yyyy")));

    h_hauteur = new VigiCruesHauteur;
    connect(h_hauteur,SIGNAL(received()),this,SLOT(printHashhauteur()));

    d_debit = new VigiCruesDebit;
    connect(d_debit,SIGNAL(received()),this,SLOT(printHashDebit()));

}

DialogVigicrues::~DialogVigicrues()
{
    delete ui;
}

void DialogVigicrues::printHashhauteur()
{
    QHash <QString, QVariant>hash_hauteur;
    hash_hauteur=h_hauteur->getHash();

    //compteur
    cptH = hash_hauteur.value("echcount").toInt();

    //Placement des données
    QVector<QCPGraphData> timeDataH(cptH);
    QDateTime convDateTimeH;
    double valeurMax = 0, valeur;

    for (int i=0; i<cptH; ++i)
    {
        convDateTimeH = hash_hauteur.value((QString ("date_obs%1").arg(i))).toDateTime();
        timeDataH[i].key = convDateTimeH.toTime_t();
        valeur = (hash_hauteur.value(QString ("resultat_obs%1").arg(i)).toDouble())/1000;
        //timeDataH[i].value = (hash_hauteur.value(QString ("resultat_obs%1").arg(i)).toDouble())/1000;
        timeDataH[i].value = valeur;
        if (valeur > valeurMax) valeurMax = valeur;
    }

    ui->widgetGraph->graph(0)->data()->set(timeDataH);

    // EChelle axe des x
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm \n dd/MM/yy");  //d. MMMM\nyyyy
    ui->widgetGraph->xAxis->setTicker(dateTicker);

    // Taille de police plus compacte pour le nom des axes
    ui->widgetGraph->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    ui->widgetGraph->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    // Nom des axes
    ui->widgetGraph->xAxis->setLabel("temps (h)");
    ui->widgetGraph->yAxis->setLabel("Hauteur (m)");

    // Echelle des axes
    if ( valeurMax < 1.5) {valeurMax = int(valeurMax)+0.5;} else {valeurMax = int(valeurMax)+1;}
    ui->widgetGraph->yAxis->setRange(0.750, valeurMax); //setRange(750, 1100); setRange0.750, 1.200; //rescale(true);
    ui->widgetGraph->xAxis->rescale(true);

    // Legende
    ui->widgetGraph->legend->setVisible(true);
    ui->widgetGraph->graph(0)->setName("Hauteur");
    ui->widgetGraph->replot();
}

void DialogVigicrues::printHashDebit()
{
    QHash <QString, QVariant>hash_debit;
    hash_debit=d_debit->getHash();

    //Compteur
    cptD = hash_debit.value("echcount").toInt();

    //Placement des données
    QVector<QCPGraphData> timeDataD(cptD);
    QDateTime convDateTimeD;
    double valeurMax = 0, valeurMx;

    for (int i=0; i<cptD; ++i)
    {
        convDateTimeD = hash_debit.value(QString ("date_obs%1").arg(i)).toDateTime();
        timeDataD[i].key = convDateTimeD.toTime_t();
        //timeDataD[i].value = (hash_debit.value(QString ("resultat_obs%1").arg(i)).toDouble())/1000;
        valeurMx = (hash_debit.value(QString ("resultat_obs%1").arg(i)).toDouble())/1000;
        timeDataD[i].value = valeurMx;
        if (valeurMx > valeurMax) valeurMax = valeurMx;
    }

    ui->widgetGraph->graph(1)->data()->set(timeDataD);

    // Taille de police plus compacte pour le nom des axes
    ui->widgetGraph->yAxis2->setTickLabelFont(QFont(QFont().family(), 8));

    // Nom de l'axe y de droite
    ui->widgetGraph->yAxis2->setLabel("Debit (m^3/s)");

    // Rendre visible l'axe des abscisse du haut:
    ui->widgetGraph->xAxis2->setVisible(true);
    ui->widgetGraph->xAxis2->setTicks(false);
    ui->widgetGraph->xAxis2->setTickLabels(false);
    ui->widgetGraph->yAxis2->setVisible(true);

    // Echelle des axes

    ui->widgetGraph->yAxis2->setRange(120, int(valeurMax/10)*10+10); //rescale(true)
    ui->widgetGraph->xAxis->rescale(true);

    // Légende
    ui->widgetGraph->legend->setVisible(true);
    ui->widgetGraph->graph(1)->setName("Debit");

    ui->widgetGraph->replot();
}
