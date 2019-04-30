#addToCoord

This class that calculates the GPS coordinates of a postal address.

##Getting Started
This class was coded in Qt. It contains a method that calculates the coordinates of a postal address. The latter is passed as a parameter in the constructor.
The coordinates are calculated using Here Maps.
If the calculation is not done correctly, the coordinates will have the value (-1; -1).

##Running the tests
In the example, we want to calculate the GPS coordinates of the address "6 RUE ROUGEMONT 75009 PARIS".

	#include "addrtocoord.h"
	
	int main(int argc, char *argv[])
	{
	    QCoreApplication a(argc, argv);
	
	    addrToCoord *coord = new addrToCoord(qApp, "6 RUE ROUGEMONT 75009 PARIS");
	    qDebug() << coord->getLatitude() << "\t" << coord->getLongitude();
	    delete coord;
	    return EXIT_SUCCESS;
	}

###Result:
	48.8716 	 2.34599
	
