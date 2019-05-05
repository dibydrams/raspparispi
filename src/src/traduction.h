#ifndef TRADUCTION_H
#define TRADUCTION_H

#include "Abstract_API.h"
#include "QNetworkReply"


class traduction : public Abstract_API
{
public:
    traduction();
    int getId() override;
    QPixmap getPixmap() override;


public slots:
    void getInfo() override;


};

#endif // TRADUCTION_H
