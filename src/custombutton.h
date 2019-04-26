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
    int buttonID;

private:
    QPixmap icon;

};

#endif // CUSTOMBUTTON_H
