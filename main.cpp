#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget> //Erlaubt befehle wie moven des Windows
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(400,450); // größe des Windows
    w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());// Holt sich die Maße der Auflösung, und ermittelt den mittelpunkt. Dann zieht er das Calc window ab um in der Mitte zu starten.
    w.show(); // Displayed das Fenster

    return a.exec();
}
