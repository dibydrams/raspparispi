#include "resetbuttons.h"

resetButtons::resetButtons()
{

}

Abstract_API::API_index resetButtons::getId()
{
    return RESET;
}

QPixmap resetButtons::getPixmap()
{
    return QPixmap(":/Icons/reseticon.png");
}

void resetButtons::getInfo()
{

}
