#include "tools.h"

Tools::Tools()
{

}

QJsonDocument Tools::LoadJson(QString fileName)
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}
