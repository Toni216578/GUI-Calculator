#ifndef ZEILENEINGABE_H // Header Datei welche für die Zeileneingabe benötigt werden, für die Matlab eingabe.
#define ZEILENEINGABE_H

#include <QDialog>
#include <QListWidgetItem>
#include <stdio.h> //Standart I/O Bibliothek
#include <stdlib.h> //Standart Bibliothek
#include <string.h> //Bibliothek, um mit Strings zu arbeiten
#include <ctype.h> //Bibliothek zum prüfen von Strings (hier: auf Zahlen)
#include <math.h> //Bibliothek für Rechnungen (hier: Pow und Modulo)

namespace Ui {
class Zeileneingabe;
}

class Zeileneingabe : public QDialog
{
    Q_OBJECT

public:
    explicit Zeileneingabe(QWidget *parent = 0);
    ~Zeileneingabe();

private slots:
    void on_pushButton_clicked();
    QString calculating(QString eingabe);




    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Zeileneingabe *ui;
};

#endif // ZEILENEINGABE_H
