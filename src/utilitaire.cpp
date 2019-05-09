#include "utilitaire.h"

utilitaire::utilitaire(){}

bool utilitaire::inMap(double lat, double lon)
{
    if(lat >= WidgetMap::BBOXminLatitude && lat <= WidgetMap::BBOXmaxLatitude && lon >= WidgetMap::BBOXminLongitude && lon <=WidgetMap::BBOXmaxLongitude) return true;
    return false;
}
