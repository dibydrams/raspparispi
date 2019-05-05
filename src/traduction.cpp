#include "traduction.h"

traduction::traduction()
{

}

Abstract_API::API_index traduction::getId()
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
