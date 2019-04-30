/********************************************************************************
** Form generated from reading UI file 'uiratp.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIRATP_H
#define UI_UIRATP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Uiratp
{
public:
    QHBoxLayout *horizontalLayout_5;
    QStackedWidget *MainStackedWidget;
    QWidget *StationPage;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *StationTitle;
    QStackedWidget *StationWidget;
    QWidget *SearchPage;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *SearchTitle;
    QHBoxLayout *horizontalLayout;
    QRadioButton *BusRadio;
    QRadioButton *MetroRadio;
    QRadioButton *RailRadio;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *TransportLabel;
    QComboBox *TransportCombo;
    QHBoxLayout *horizontalLayout_4;
    QLabel *StationLabel;
    QComboBox *StationCombo;
    QPushButton *RequestButton;
    QScrollArea *scrollArea;
    QWidget *ScrollAreaContents;

    void setupUi(QDialog *Uiratp)
    {
        if (Uiratp->objectName().isEmpty())
            Uiratp->setObjectName(QString::fromUtf8("Uiratp"));
        Uiratp->resize(577, 438);
        horizontalLayout_5 = new QHBoxLayout(Uiratp);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        MainStackedWidget = new QStackedWidget(Uiratp);
        MainStackedWidget->setObjectName(QString::fromUtf8("MainStackedWidget"));
        StationPage = new QWidget();
        StationPage->setObjectName(QString::fromUtf8("StationPage"));
        horizontalLayout_2 = new QHBoxLayout(StationPage);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        StationTitle = new QLabel(StationPage);
        StationTitle->setObjectName(QString::fromUtf8("StationTitle"));
        StationTitle->setMinimumSize(QSize(0, 50));
        StationTitle->setMaximumSize(QSize(16777215, 50));
        StationTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(StationTitle);

        StationWidget = new QStackedWidget(StationPage);
        StationWidget->setObjectName(QString::fromUtf8("StationWidget"));

        verticalLayout->addWidget(StationWidget);


        horizontalLayout_2->addLayout(verticalLayout);

        MainStackedWidget->addWidget(StationPage);
        SearchPage = new QWidget();
        SearchPage->setObjectName(QString::fromUtf8("SearchPage"));
        verticalLayout_4 = new QVBoxLayout(SearchPage);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        SearchTitle = new QLabel(SearchPage);
        SearchTitle->setObjectName(QString::fromUtf8("SearchTitle"));
        SearchTitle->setMinimumSize(QSize(0, 50));
        SearchTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(SearchTitle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        BusRadio = new QRadioButton(SearchPage);
        BusRadio->setObjectName(QString::fromUtf8("BusRadio"));
        BusRadio->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(BusRadio, 0, Qt::AlignHCenter);

        MetroRadio = new QRadioButton(SearchPage);
        MetroRadio->setObjectName(QString::fromUtf8("MetroRadio"));
        MetroRadio->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(MetroRadio, 0, Qt::AlignHCenter);

        RailRadio = new QRadioButton(SearchPage);
        RailRadio->setObjectName(QString::fromUtf8("RailRadio"));
        RailRadio->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(RailRadio, 0, Qt::AlignHCenter);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        TransportLabel = new QLabel(SearchPage);
        TransportLabel->setObjectName(QString::fromUtf8("TransportLabel"));

        horizontalLayout_3->addWidget(TransportLabel, 0, Qt::AlignHCenter);

        TransportCombo = new QComboBox(SearchPage);
        TransportCombo->setObjectName(QString::fromUtf8("TransportCombo"));
        TransportCombo->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(TransportCombo);


        horizontalLayout_6->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        StationLabel = new QLabel(SearchPage);
        StationLabel->setObjectName(QString::fromUtf8("StationLabel"));

        horizontalLayout_4->addWidget(StationLabel, 0, Qt::AlignHCenter);

        StationCombo = new QComboBox(SearchPage);
        StationCombo->setObjectName(QString::fromUtf8("StationCombo"));
        StationCombo->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(StationCombo);


        horizontalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_6);

        RequestButton = new QPushButton(SearchPage);
        RequestButton->setObjectName(QString::fromUtf8("RequestButton"));

        verticalLayout_2->addWidget(RequestButton);


        verticalLayout_3->addLayout(verticalLayout_2);

        scrollArea = new QScrollArea(SearchPage);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        ScrollAreaContents = new QWidget();
        ScrollAreaContents->setObjectName(QString::fromUtf8("ScrollAreaContents"));
        ScrollAreaContents->setGeometry(QRect(0, 0, 537, 231));
        scrollArea->setWidget(ScrollAreaContents);

        verticalLayout_3->addWidget(scrollArea);


        verticalLayout_4->addLayout(verticalLayout_3);

        MainStackedWidget->addWidget(SearchPage);

        horizontalLayout_5->addWidget(MainStackedWidget);

#ifndef QT_NO_SHORTCUT
        TransportLabel->setBuddy(TransportCombo);
        StationLabel->setBuddy(StationCombo);
#endif // QT_NO_SHORTCUT

        retranslateUi(Uiratp);

        MainStackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Uiratp);
    } // setupUi

    void retranslateUi(QDialog *Uiratp)
    {
        Uiratp->setWindowTitle(QApplication::translate("Uiratp", "Dialog", nullptr));
        StationTitle->setText(QApplication::translate("Uiratp", "Station Page", nullptr));
        SearchTitle->setText(QApplication::translate("Uiratp", "Search Page", nullptr));
        BusRadio->setText(QApplication::translate("Uiratp", "&Bus", nullptr));
        MetroRadio->setText(QApplication::translate("Uiratp", "&Metro", nullptr));
        RailRadio->setText(QApplication::translate("Uiratp", "&Rail", nullptr));
        TransportLabel->setText(QApplication::translate("Uiratp", "&Transport :", nullptr));
        StationLabel->setText(QApplication::translate("Uiratp", "&Station :", nullptr));
        RequestButton->setText(QApplication::translate("Uiratp", "Send Request", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Uiratp: public Ui_Uiratp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIRATP_H
