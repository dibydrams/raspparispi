#include "transport.h"

Transport::Transport(QString t_externalcode_line, QString t_shortNameLine, QString t_shortGroupOfLines, QString t_networkName, QString t_transportMode, int t_accessibility, int t_myIndex)
{
    codeLine = t_externalcode_line;
    shortNameLine = t_shortNameLine;
    shortGroupOfLines = t_shortGroupOfLines;
    networkName = t_networkName;
    transportMode = StringToEnum(t_transportMode);
    accessibility = t_accessibility;
    myIndex = t_myIndex;

    if(networkName != "")
    {
        nameShowed = shortNameLine + " (" + networkName + ')';
    }
    else
    {
        nameShowed = shortNameLine;
    }

}

bool Transport::compareTransports(const Transport &t1, const Transport &t2)
{
    if(t1.shortNameLine != t2.shortNameLine)
    {
        return t1.shortNameLine < t2.shortNameLine;
    }
    return 0;
}

Transport::Modes Transport::StringToEnum(QString _strMode)
{
    if(_strMode == "bus")
    {
        return Transport::Modes::bus;
    }
    else if (_strMode == "funicular")
    {
        return Transport::Modes::funicular;
    }
    else if (_strMode == "metro")
    {
        return Transport::Modes::metro;
    }
    else if (_strMode == "rail")
    {
        return Transport::Modes::rail;
    }
    else
    {
        return Transport::Modes::tram;
    }
}
