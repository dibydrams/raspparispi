#include "traduction.h"

traduction::traduction()
{

}

int traduction::getId()
{
    return TRADUCTION;
}

QPixmap traduction::getPixmap()
{
 return QPixmap(":/Icons_meteo/translation.png");
}

void traduction::getInfo()
{

}
