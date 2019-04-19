#ifndef TOOLS_H
#define TOOLS_H

#include <QJsonDocument>
#include <QFile>

class Tools
{
public:
    Tools();
    static QJsonDocument LoadJson(QString fileName);
};

#endif // TOOLS_H
