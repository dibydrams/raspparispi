#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QPixmap>

#include "apievenementsmv.h"
#include "icon.h"

class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CustomButton(Abstract_API *ptr,QWidget *parent = nullptr);
    Abstract_API *ptrAPI;
    Abstract_API::API_index buttonID;

private:
    QPixmap icon;

signals:
    void Clicked(Abstract_API *ptr);
    void ClickedEmpty(Abstract_API *ptr);
    void Finished();
    void RazSig(Abstract_API::API_index buttonID);

private slots:
    void ClickedManage();
    void FinishedReceived();
};

#endif // CUSTOMBUTTON_H
