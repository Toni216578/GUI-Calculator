#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QLineEdit>
#include "zeileneingabe.h"
#include <QMessageBox>
#include "winkel.h"
#include <QColor>

#include <cmath> // Mathe
#include <QtCore/QCoreApplication> // Stell eine Event Loop für nicht Gui event zurverfügung.

QString value = "", total = "", memory = ""; // String damit die Zahlen auf dem Display anzuzeigen sind.
float digitValue=0, First=0, Second=0, pi = 3.14159265359; // Zahlen
bool addibool = false, subtbool = false, multibool = false, dividebool = false, powbool = false, modbool = false , equalsbool = false, inversebool = false, sqrtbool = false, tanbool = false, sinbool = false, cosbool=false, expbool = false, logbool = false; //powbool war true?!
bool isResult = false, switchanglebool = false;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    QFont font;
    QPalette p=palette();
    p.setBrush(QPalette::ButtonText,Qt::darkCyan);
    winkel_call = new Winkel(this); //nur eine instanz!
    font.setPointSize(14);
    display = new QLabel("", this); // Created ein neues Label
    display->setGeometry(QRect(QPoint(50,-50), QSize(250,200))); // Setzt die Postiiton im Fenster.
    display->setFont(font);
    font.setPointSize(10);
    memorydisplay = new QLabel("", this); //Label für M
    memorydisplay->setGeometry(QRect(QPoint(50,-15), QSize(250,200))); // Setzt die Postiiton im Fenster.
    memorydisplay->setFont(font);
    equals(); // Behebt den Speicherfehler.
    CE();// Behebt den Speicherfehler, welcher durch Schon beschrieben Speicher beim Start des Programmes Auftaucht.


    // Der Folgende Teil Erstellt die Buttons mit einer Angegeben Position und Verknüpft diese mit eine Methode.

    zeile_button= new QPushButton("Matlab", this); // Erstellt den Button für die Matlab eingabe
    zeile_button ->setGeometry(QRect(QPoint(200,100), QSize(50,50))); //Setzt die Position
    connect(zeile_button, SIGNAL(released()), this, SLOT(zeile())); // Auf Release wird das command zeile ausgeführt.
    zeile_button->setFont(font); // Schriftart

    winkel_button= new QPushButton("Winkel", this);
    winkel_button ->setGeometry(QRect(QPoint(250,100), QSize(50,50)));
    connect(winkel_button, SIGNAL(released()), this, SLOT(winkel()));
    winkel_button->setFont(font);

    font.setPointSize(12);
    MC_button = new QPushButton("MC", this);
    MC_button ->setGeometry(QRect(QPoint(50,100), QSize(50,50)));
    connect(MC_button, SIGNAL(released()), this, SLOT(MC()));
    MC_button->setFont(font);

    MR_button = new QPushButton("MR", this);
    MR_button ->setGeometry(QRect(QPoint(100,100), QSize(50,50)));
    connect(MR_button, SIGNAL(released()), this, SLOT(MR()));
    MR_button->setFont(font);

    MS_button = new QPushButton("MS", this);
    MS_button ->setGeometry(QRect(QPoint(150,100), QSize(50,50)));
    connect(MS_button, SIGNAL(released()), this, SLOT(MS()));
    MS_button->setFont(font);

    sin_button = new QPushButton("sin", this);
    sin_button ->setGeometry(QRect(QPoint(300,250), QSize(50,50)));
    connect(sin_button, SIGNAL(released()), this, SLOT(sin()));
    sin_button->setFont(font);

    cos_button = new QPushButton("cos", this);
    cos_button ->setGeometry(QRect(QPoint(300,200), QSize(50,50)));
    connect(cos_button, SIGNAL(released()), this, SLOT(cos()));
    cos_button->setFont(font);

    tan_button= new QPushButton("tan", this);
    tan_button ->setGeometry(QRect(QPoint(300,150), QSize(50,50)));
    connect(tan_button, SIGNAL(released()), this, SLOT(tan()));
    tan_button->setFont(font);

    switch_button= new QPushButton("Rad", this);
    switch_button ->setGeometry(QRect(QPoint(300,100), QSize(50,50)));
    connect(switch_button, SIGNAL(released()), this, SLOT(switchangle()));
    switch_button->setFont(font);
    switch_button->setPalette(p);

    exp_button = new QPushButton("*e^", this);
    exp_button ->setGeometry(QRect(QPoint(250,300), QSize(50,50)));
    connect(exp_button, SIGNAL(released()), this, SLOT(exp()));
    exp_button->setFont(font);

    log_button = new QPushButton("log", this);
    log_button ->setGeometry(QRect(QPoint(250,350), QSize(50,50)));
    connect(log_button, SIGNAL(released()), this, SLOT(log()));
    log_button->setFont(font);

    sqrt_button= new QPushButton("Sqrt", this);
    sqrt_button ->setGeometry(QRect(QPoint(200,150), QSize(50,50)));
    connect(sqrt_button, SIGNAL(released()), this, SLOT(sqrt()));
    sqrt_button->setFont(font);
    //

    inverse_button= new QPushButton("1/x", this);
    inverse_button ->setGeometry(QRect(QPoint(250,150), QSize(50,50)));
    connect(inverse_button, SIGNAL(released()), this, SLOT(inverse()));
    inverse_button->setFont(font);

    neg_button = new QPushButton("+/-", this);
    neg_button ->setGeometry(QRect(QPoint(50,150), QSize(50,50)));
    connect(neg_button, SIGNAL(released()), this, SLOT(neg()));
    neg_button->setFont(font);

    CE_button = new QPushButton("CE", this);
    CE_button ->setGeometry(QRect(QPoint(150,150), QSize(50,50)));
    connect(CE_button, SIGNAL(released()), this, SLOT(CE()));
    CE_button->setFont(font);

    C_button = new QPushButton("C", this);
    C_button ->setGeometry(QRect(QPoint(100,150), QSize(50,50)));
    connect(C_button, SIGNAL(released()), this, SLOT(C()));
    C_button->setFont(font);

    font.setPointSize(16);
    equals_button = new QPushButton("=", this);
    equals_button ->setGeometry(QRect(QPoint(300,300), QSize(50,100)));
    connect(equals_button, SIGNAL(released()), this, SLOT(equals()));
    equals_button->setFont(font);

    addi_button = new QPushButton("+", this);
    addi_button ->setGeometry(QRect(QPoint(200,300), QSize(50,50)));
    connect(addi_button, SIGNAL(released()), this, SLOT(addi()));
    addi_button->setFont(font);

    subt_button = new QPushButton("-", this);
    subt_button ->setGeometry(QRect(QPoint(200,350), QSize(50,50)));
    connect(subt_button, SIGNAL(released()), this, SLOT(subt()));
    subt_button->setFont(font);

    multi_button = new QPushButton("*", this);
    multi_button ->setGeometry(QRect(QPoint(200,250), QSize(50,50)));
    connect(multi_button, SIGNAL(released()), this, SLOT(multi()));
    multi_button->setFont(font);

    divide_button = new QPushButton("/", this);
    divide_button ->setGeometry(QRect(QPoint(200,200), QSize(50,50)));
    connect(divide_button, SIGNAL(released()), this, SLOT(divide()));
    divide_button->setFont(font);

    pow_button = new QPushButton("^", this);
    pow_button ->setGeometry(QRect(QPoint(250,250), QSize(50,50)));
    connect(pow_button, SIGNAL(released()), this, SLOT(pow()));
    pow_button->setFont(font);

    mod_button = new QPushButton("mod", this);
    mod_button ->setGeometry(QRect(QPoint(250,200), QSize(50,50)));
    connect(mod_button, SIGNAL(released()), this, SLOT(modulo()));
    mod_button->setFont(font);

    point_button = new QPushButton(".", this);
    point_button ->setGeometry(QRect(QPoint(150,350), QSize(50,50)));
    connect(point_button, SIGNAL(released()), this, SLOT(pointclicked()));
    point_button->setFont(font);




    for(int i = 0; i<10; i++){
        QString digit = QString::number(i); // Neuer String welcher den jeweiligen wert bekommt für number(i)
        num_button[i] = new QPushButton(digit, this); // Erstellt ein einen Button mit dem Index i
        connect(num_button[i], SIGNAL(released()), this, SLOT(digitclicked())); // Jedem erstellten button wird die funktion digitclicked zugeordnet.
        //        font.setPointSize(16);
        font.setPointSize(32);
        num_button[i]->setFont(font);
        //        num_button[i]->setEnabled(false);
    }
    setposition(); // Führt die Funktion aus
    First = 0; //test


}

void MainWindow::setposition(){ //Setzt die Position der Einzelnen Zahlen, da dies repetiv ist wurde es in Schleifen verpackt.
    for(int i =0;i<1; i++){
        num_button[i] -> setGeometry(QRect(QPoint(50,350), QSize(100,50)));
    }
    for(int i = 1; i<4; i++){
        num_button[i] -> setGeometry(QRect(QPoint(50*i,300),QSize(50,50))); // Geometry der Buttons

    }
    for(int i = 4; i<7; i++){
        num_button[i] -> setGeometry(QRect(QPoint(50*(i-3),250),QSize(50,50)));
    }
    for(int i = 7; i<10; i++){
        num_button[i] -> setGeometry(QRect(QPoint(50*(i-6),200),QSize(50,50)));
    }
}

void MainWindow::digitclicked(){ // Wenn eine Zahl geklickt wurde wird die Zahl im Display wiedergegeben
    deleteIfResult(); //Schaut ob das Display gelöscht werden kann.
    if(isResult){
        display -> setText("");
        isResult = false;
    }
    if (display->text() == "0"){
        display->setText("");
    }
    QPushButton *button = (QPushButton*)sender(); // Der sender bekommte und sendet verschieden values
    emit numbersend(button->text()[0].digitValue()); // Es bekommt die nummer, welchger der Button von oben, welcher seine values aus dem Pushbutton bekommt. Dann wird die nummer in einen Text umgewandelt und dann das digitvalue ausgelesen.
    int displayValue = button->text().toInt();  // Konvertiert den Text vom button in eine Integer
    if (display->text() == "0" && displayValue == 0.0) // Schaut ob im Dispaly bereits eine Null steht und ob Null gedrückt wurd eum keine 00 im display zuhaben.
        return;
    display->setText(display->text() + QString::number(displayValue)); // Kombiniert den Inhalt des Display mit der gepressten nummer
    digitValue = display->text().toFloat(); // Digitvalue zwischen speicher der zahl
}

void MainWindow::CE(){    // Methode die alle Variablen reseted und den Taschenrechner in Ausgangszustand versetzt.
    value = "";
    display -> setText("");
    equalsbool = false;
    First = 0;
    Second = 0;// resetted alle werte
    digitValue = 0;
    isResult = false;
    addibool = false;
    subtbool = false;
    multibool = false;
    dividebool = false;
    powbool = false;
    modbool = false;
    inversebool = false;
    sqrtbool = false;
    tanbool = false;
    sinbool = false;
    cosbool=false;
    expbool = false;
    logbool = false;



}

void MainWindow::C(){
    if(equalsbool){ //Für Eingabe nach "=" zum löschen des Displays
        CE();
    }// Methoden für die Buttons
    QString temp;
    temp = display->text(); //Sonst wird nur der Letzte Teil des Display gelöscht.
    temp.remove(temp.length() - 1, temp.length());
    display->setText(temp);
    digitValue = temp.toFloat();

}

void MainWindow::equals(){// wenn = gedrückt wird, wird geschaut ob der jeweilige bool true ist und dann die rechen operation ausgeführt

    if(isResult){
        return;
    }

    Second = digitValue;

    if(expbool){
        total = QString::number(First * std::exp(Second)); // Es wird die Exponentialfunktion gebildet
        expbool = false;
    }
    if(logbool){
        total = QString::number(std::log(Second)); //Logarithmus funktion.
        logbool = false;
    }
    if(tanbool){
        if(switchanglebool){
            Second = 360/(2*pi)*Second; // Schaut in welchem Winkelmaß gerechnet wird
        }
        total = QString::number(std::tan(Second)); // es wird der Tangents gebildet
        tanbool = false;
    }
    if(sinbool){

        if(switchanglebool){
            Second = 360/(2*pi)*Second; // Schaut in welchem Winkelmaß gerechnet wird
        }
        total = QString::number(std::sin(Second)); // es wird der Sinus gebildet
        sinbool = false;
    }
    if(cosbool){
        if(switchanglebool){ // Schaut in welchem Winkelmaß gerechnet wird
            Second = 360/(2*pi)*Second;
        }
        total = QString::number(std::cos(Second)); // Es wird der Cosinus gebildet.
        cosbool = false;
    }
    if(sqrtbool){
        total = QString::number(std::sqrt(Second)); // Es wird der string aus der Wurzel gebildet.
        sqrtbool = false;
    }
    if(inversebool){
        total = QString::number(1/Second); // Es wird die Zahl invertiert
        inversebool = false;
    }
    if(addibool){
        total = QString::number(First+Second); // es wird ein String aus der Ersten zahl + der zweiten gebildet und dann gedisplayed
        addibool = false;
    }
    if(subtbool){
        total = QString::number(First-Second); // es wird ein String aus der Ersten zahl - der zweiten gebildet und dann gedisplayed
        subtbool= false;
    }
    if(multibool){
        total = QString::number(First*Second); // es wird ein String aus der Ersten zahl * der zweiten gebildet und dann gedisplayed
        multibool = false;
    }
    if(dividebool){
        total = QString::number(First/Second);// es wird ein String aus der Ersten zahl / der zweiten gebildet und dann gedisplayed
        if(Second == 0){
            div_zero();
        }
        dividebool = false;
    }
    if(powbool){
        total = QString::number(std::pow(First, Second)); // es wird ein Strin aus der Ersten zahl hoch der zweiten gebildet
        powbool = false;
    }
    if(modbool){
        int Firstmod = First; // die Zahle müssen von float in integer umgewandelt werde da sonst der Modulo operator nicht funktioniert.
        int Secondmod = Second;
        //        if(Firstmod ==0 && Secondmod==0 || Secondmod == 0){
        if(Secondmod == 0){
            mod_zero();
            return;
        }
        else{
            total = QString::number(Firstmod%Secondmod); // Modulo Rechnung
            modbool = false;}
    }
    display -> setText(total); // Ergebnis wird dargestellt
    equalsbool = true; // Wenn bool true ist dann wird das Ergebnis in die erste zahl gespeichert um direkt damit weiter zurechnen.
    First = total.toFloat();
    Second = 0;
    digitValue=total.toFloat();

}
// Im folgenden Teil werden die Bools gesetzt wenn die Jeweilige operation gedrückt wird, um diese dann weiter oben abzufragen.

void MainWindow::addi(){
    CalcIfPressedTwice();
    addibool = true;
}
void MainWindow::subt(){
    CalcIfPressedTwice();
    subtbool = true;
}
void MainWindow::multi(){
    CalcIfPressedTwice();
    multibool = true;
}
void MainWindow::divide(){
    CalcIfPressedTwice();
    dividebool = true;
}
void MainWindow::pow(){
    CalcIfPressedTwice();
    powbool = true;
}
void MainWindow::modulo(){
    CalcIfPressedTwice();
    modbool = true;
}

void MainWindow::sqrt(){
    CalcIfPressedTwiceAndDirectResult();
    sqrtbool = true;
    equals();
}

void MainWindow::neg(){ // Methode die die Zahl im DIsplay negiert.
    deleteIfResult();
    display->setText(QString::number(display->text().toFloat()*(-1))); // Negiert das Display
    digitValue=digitValue*(-1); //Negiert die Zahl
}

void MainWindow::pointclicked(){
    deleteIfResult();
    if ( !display->text().isEmpty() && !display->text().contains('.')){
        display->setText(display->text() + tr(".")); // Setzt den Punkt jedoch wird diese rnicht kovertiert
    }

}

void MainWindow::deleteIfResult(){
    if(equalsbool && !(addibool || subtbool || multibool || dividebool || powbool || modbool)){ //Für Eingabe nach "=" zum löschen des Displays
        CE();
    }
}

void MainWindow::CalcIfPressedTwice(){
    if(addibool || subtbool || multibool || dividebool || powbool || modbool){ // Falls zwischen Operationen nicht "=" gedrückt wird, wird equals() ausgeführt
        equals();
        isResult = true;
    }
    else{ //sonst Display leeren, damit 2. Zahl eingegeben werden kann
        display -> setText("");
    }
    if(!equalsbool){ //Falls erste Operation, Variable speichern
        First = digitValue;
        digitValue=0;
    }
}
void MainWindow::CalcIfPressedTwiceAndDirectResult(){
    if(addibool || subtbool || multibool || dividebool || powbool || modbool){ // Falls zwischen Operationen nicht "=" gedrückt wird, wird equals() ausgeführt (abgeänderte Version für Operationen, die keine 2. Eingabe erfordern)
        equals();
    }
    isResult = false;
}

void MainWindow::mod_zero(){ // Fehler ausgabe bei Modulo mit 0
    QMessageBox::warning(this,"ERROR","Mod of zero is not allowed!"); //
}

void MainWindow::div_zero(){ // Fehler ausgabe bei Division mit 0
    QMessageBox::warning(this,"ERROR","Division with zero is not allowed!"); //
}

void MainWindow::MC(){ // Memory clearen
    memory = "";
    memorydisplay->setText("");
}

void MainWindow::MR(){ // Memory DIsplayen und in die Zahl Speichern
    display->setText(memory);
    digitValue = memory.toFloat();
    total = memory;
    First = memory.toFloat();
}

void MainWindow::MS(){ // Zahl in Memory Speichern
    memorydisplay->setText("<font color='darkMagenta'> M = "+display->text()+"</font>");
    memory = display->text();
    isResult = true;
}


void MainWindow::inverse(){ //Methode die den Bool des Invertieren auf true setzt
    CalcIfPressedTwiceAndDirectResult();
    inversebool = true;
    equals();
}



void MainWindow::zeile(){ //button für 2nd fenster
    Zeileneingabe zeileneingabe;
    zeileneingabe.setModal(true);
    zeileneingabe.exec();
}

void MainWindow::winkel(){ //Methode die das Winkel Fenster Öffnet
    winkel_call->show();
}


void MainWindow::tan(){ // Setzt den Bool für Tan auf true.
    CalcIfPressedTwiceAndDirectResult();
    tanbool = true;
    equals();
}

void MainWindow::sin(){ // Setzt den Bool für Sin auf true.
    CalcIfPressedTwiceAndDirectResult();
    sinbool = true;
    equals();
}

void MainWindow::cos(){ // Setzt den Bool für cos auf true.
    CalcIfPressedTwiceAndDirectResult();
    cosbool = true;
    equals();
}

void MainWindow::switchangle(){ // Setzt den bool für das Winkelmaß damit bei der Rechnung das richtige Winkelmaß genommen wird.
    if(!switchanglebool){
        switchanglebool = true; //true = deg
        switch_button->setText("Deg");
    }
    else if(switchanglebool){
        switchanglebool = false; // false = rad
        switch_button->setText("Rad");
    }
}

void MainWindow::exp(){ //Bool für die Exponentialfunktion
    CalcIfPressedTwice();
    expbool = true;
}

void MainWindow::log(){ // Bool für die Logarithmus Funktion
    CalcIfPressedTwiceAndDirectResult();
    logbool = true;
    equals();
}

MainWindow::~MainWindow()
{
}
