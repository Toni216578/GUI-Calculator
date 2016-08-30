#include "winkel.h"
#include "ui_winkel.h"
// Fenster welches das Umrechnen von WInkeln erlaubt.
Winkel::Winkel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Winkel)
{
    ui->setupUi(this);
}
Winkel::~Winkel()
{
    delete ui;
}

void Winkel::on_pushButton_clicked() //Es wird das Winkelmaß Deg in Rad geändert
{
    double rad=0;
    double deg=0;
    deg = ui->lineEdit->text().toDouble(); // Holt sich den Input und speichert ihn in Deg
    rad = (2*3.14159265359)/360*deg; // Wandelt Deg in Rad Um und speichert diesen in Rad
    ui->lineEdit_2->setText(QString::number(rad)); // Gibt Rad im Display aus.

}

void Winkel::on_pushButton_2_clicked() //Es wird das Winkelmaß Rad in Deg geändert
{
    double rad=0;
    double deg=0;
    rad = ui->lineEdit_2->text().toDouble(); // Holt sich  den Input und speichert ihn in Rad
    deg = 360/(2*3.14159265359)*rad; // Wandelt Rad in Deg um und speichert diesen in deg
    ui->lineEdit->setText(QString::number(deg)); // gibt Deg im Display aus
}
