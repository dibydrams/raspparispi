#include "dialoginfo.h"
#include "ui_dialoginfo.h"
#include <QVBoxLayout>
#include <QTableWidget>

dialoginfo::dialoginfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialoginfo)
{
    ui->setupUi(this);
  //  verticalLayout_3 = new QVBoxLayout(ui->scrollAreaWidgetContents);


    tableWidget = new QTableWidget(this);

    ui->verticalLayout->addWidget(tableWidget);

//    tableWidget_2 = new QTableWidget(ui->scrollAreaWidgetContents);
//    tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));

//    verticalLayout->addWidget(tableWidget_2);

//    tableWidget_3 = new QTableWidget(ui->scrollAreaWidgetContents);
//    tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));

//    verticalLayout->addWidget(tableWidget_3);


//    verticalLayout_3->addLayout(verticalLayout);


//    verticalLayout_2->addWidget(ui->scrollArea);
}

dialoginfo::~dialoginfo()
{
    delete ui;
}
