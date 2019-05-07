#ifndef DIALOGVIGICRUES_H
#define DIALOGVIGICRUES_H

#include <QDialog>
#include "vigicrueshauteur.h"
#include "vigicruesdebit.h"

namespace Ui {
class DialogVigicrues;
}

class DialogVigicrues : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVigicrues(QWidget *parent = nullptr);
    ~DialogVigicrues();

private:
    Ui::DialogVigicrues *ui;
    VigiCruesHauteur *h_hauteur;
    VigiCruesDebit *d_debit;
    int cptH;
    int cptD;

private slots:
    void printHashhauteur();
    void printHashDebit();
};

#endif // DIALOGVIGICRUES_H
