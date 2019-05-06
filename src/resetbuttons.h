#ifndef RESETBUTTONS_H
#define RESETBUTTONS_H

#include "Abstract_API.h"

class resetButtons : public Abstract_API
{
public:
    resetButtons();
    API_index getId() override;
    QPixmap getPixmap() override;

public slots:
    void getInfo() override;
};

#endif // RESETBUTTONS_H
