#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit> // Included Labels Buttons und Lines
#include <Qwidget>
#include "winkel.h"
#include "zeileneingabe.h"

namespace Ui {
class MainWindow;
}
class Button;
class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    numbersend(int number); // Signal welches benutzt wird um die nummer auszulesen.
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:   //Erstellt eine Liste aller Methoden
    void CE(); // Methode zum CEen des Screens
    void equals(); // Methode ausrechnen
    void addi();  // " Addition
    void subt(); // " Subtraktion
    void multi(); // " Multiplikation
    void divide(); // " Division
    void pow(); // " Potenz
    void modulo(); // " Modulo
    void digitclicked(); // " Zahl geclicked
    void setposition(); // " Um die Position der buttons zu setzten
    void pointclicked(); // " punkt geclicked
    void zeile();
    void neg(); // " Negativ
    void C(); // " Clear
    void deleteIfResult(); // " Löschen falls schon ein Ergebnis da ist.
    void CalcIfPressedTwice(); // "
    void CalcIfPressedTwiceAndDirectResult();
    void mod_zero(); // " Modulo mit 0
    void div_zero(); // " Division mit 0
    void winkel(); // "
    void MC(); // " Speicher Clearen
    void MR(); // " Speicher aufrufen
    void MS(); // " Speichern
    void sqrt(); // " Wurzel
    void inverse(); // "
    void tan(); // " Winkelfunktionen
    void sin();
    void cos();
    void switchangle(); // " Vertauschen von Grad/Bogenmaß
    void exp(); // " Exponential Funktion
    void log(); // " Logarithmus




private:
    QLabel *display;    // In diesem Teil werden das Label und Alle buttons deklariert
    QLabel *memorydisplay;
    QPushButton *CE_button;
    QPushButton *equals_button;
    QPushButton *addi_button;
    QPushButton *subt_button;
    QPushButton *multi_button;
    QPushButton *divide_button;
    QPushButton *pow_button;
    QPushButton *mod_button;
    QPushButton *point_button;
    QPushButton *num_button[10];
    QPushButton *zeile_button;
    QPushButton *neg_button;
    QPushButton *C_button;
    QPushButton *winkel_button;
    QPushButton *MC_button;
    QPushButton *MR_button;
    QPushButton *MS_button;
    QPushButton *sqrt_button;
    QPushButton *inverse_button;
    QPushButton *tan_button;
    QPushButton *sin_button;
    QPushButton *cos_button;
    QPushButton *switch_button;
    QPushButton *exp_button;
    QPushButton *log_button;
    Winkel *winkel_call; //für modal nicht notwendig --- ist aber nicht modal ;)

};

#endif // MAINWINDOW_H
