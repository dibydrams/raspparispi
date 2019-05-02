/********************************************************************************
** Form generated from reading UI file 'uiratp.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
            Uiratp->setObjectName(QStringLiteral("Uiratp"));
        Uiratp->resize(577, 438);
        horizontalLayout_5 = new QHBoxLayout(Uiratp);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        MainStackedWidget = new QStackedWidget(Uiratp);
        MainStackedWidget->setObjectName(QStringLiteral("MainStackedWidget"));
        StationPage = new QWidget();
        StationPage->setObjectName(QStringLiteral("StationPage"));
        horizontalLayout_2 = new QHBoxLayout(StationPage);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        StationTitle = new QLabel(StationPage);
        StationTitle->setObjectName(QStringLiteral("StationTitle"));
        StationTitle->setMinimumSize(QSize(0, 50));
        StationTitle->setMaximumSize(QSize(16777215, 50));
        StationTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(StationTitle);

        StationWidget = new QStackedWidget(StationPage);
        StationWidget->setObjectName(QStringLiteral("StationWidget"));

        verticalLayout->addWidget(StationWidget);


        horizontalLayout_2->addLayout(verticalLayout);

        MainStackedWidget->addWidget(StationPage);
        SearchPage = new QWidget();
        SearchPage->setObjectName(QStringLiteral("SearchPage"));
        verticalLayout_4 = new QVBoxLayout(SearchPage);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        SearchTitle = new QLabel(SearchPage);
        SearchTitle->setObjectName(QStringLiteral("SearchTitle"));
        SearchTitle->setMinimumSize(QSize(0, 50));
        SearchTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(SearchTitle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        BusRadio = new QRadioButton(SearchPage);
        BusRadio->setObjectName(QStringLiteral("BusRadio"));
        BusRadio->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(BusRadio, 0, Qt::AlignHCenter);

        MetroRadio = new QRadioButton(SearchPage);
        MetroRadio->setObjectName(QStringLiteral("MetroRadio"));
        MetroRadio->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(MetroRadio, 0, Qt::AlignHCenter);

        RailRadio = new QRadioButton(SearchPage);
        RailRadio->setObjectName(QStringLiteral("RailRadio"));
        RailRadio->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(RailRadio, 0, Qt::AlignHCenter);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        TransportLabel = new QLabel(SearchPage);
        TransportLabel->setObjectName(QStringLiteral("TransportLabel"));

        horizontalLayout_3->addWidget(TransportLabel, 0, Qt::AlignHCenter);

        TransportCombo = new QComboBox(SearchPage);
        TransportCombo->setObjectName(QStringLiteral("TransportCombo"));
        TransportCombo->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(TransportCombo);


        horizontalLayout_6->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        StationLabel = new QLabel(SearchPage);
        StationLabel->setObjectName(QStringLiteral("StationLabel"));

        horizontalLayout_4->addWidget(StationLabel, 0, Qt::AlignHCenter);

        StationCombo = new QComboBox(SearchPage);
        StationCombo->setObjectName(QStringLiteral("StationCombo"));
        StationCombo->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(StationCombo);


        horizontalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_6);

        RequestButton = new QPushButton(SearchPage);
        RequestButton->setObjectName(QStringLiteral("RequestButton"));

        verticalLayout_2->addWidget(RequestButton);


        verticalLayout_3->addLayout(verticalLayout_2);

        scrollArea = new QScrollArea(SearchPage);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        ScrollAreaContents = new QWidget();
        ScrollAreaContents->setObjectName(QStringLiteral("ScrollAreaContents"));
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
