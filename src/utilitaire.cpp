#include "utilitaire.h"

utilitaire::utilitaire(){}

bool utilitaire::inMap(double lat, double lon)
{
    if(lat >= minLat && lat <= maxLat && lon >= minLon && lon <=maxLon) return true;
    return false;
}
