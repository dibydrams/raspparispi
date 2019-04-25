#include "custombutton.h"
#include "Abstract_API.h"

CustomButton::CustomButton(Abstract_API *ptr, QWidget *parent) : QPushButton(parent)
{
    ptrAPI = ptr;
    icon = ptrAPI->getPixmap();
    setIcon(QIcon(icon));
    buttonID = ptr->getId();
    setFlat(true);
    setIconSize(QSize(80,80));
    resize(80,80);

}
