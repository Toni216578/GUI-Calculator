#ifndef WINKEL_H // Header Datei für die Winkel Funktionen, welche wie die Mainwindow header Datei die Funktionen verwaltet.
#define WINKEL_H

#include <QDialog>

namespace Ui {
class Winkel;
}

class Winkel : public QDialog
{
    Q_OBJECT

public:
    explicit Winkel(QWidget *parent = 0);
    ~Winkel();

private slots:
    void on_pushButton_clicked(); // Funktionen auf Button

    void on_pushButton_2_clicked();

private:
    Ui::Winkel *ui;
};

#endif // WINKEL_H
