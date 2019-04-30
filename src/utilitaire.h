#ifndef UTILITAIRE_H
#define UTILITAIRE_H

const double minLat = 48.8636;
const double maxLat = 48.8796;
const double minLon = 2.32999;
const double maxLon = 2.36199;

class utilitaire
{
public:
    utilitaire();
    static bool inMap(double lat, double lon);
};

#endif // UTILITAIRE_H
