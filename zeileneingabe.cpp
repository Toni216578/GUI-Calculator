#include "zeileneingabe.h"
#include "ui_zeileneingabe.h"
QString History;

Zeileneingabe::Zeileneingabe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zeileneingabe)
{
    ui->setupUi(this);
}

Zeileneingabe::~Zeileneingabe()
{
    delete ui;
}

void Zeileneingabe::on_pushButton_clicked()
{
    QString eingabe;
    eingabe = ui->lineEdit->text();
    ui->listWidget->addItem(ui->lineEdit->text());
    ui->textEdit->setText(calculating(eingabe));//ergebnis
}





QString Zeileneingabe::calculating(QString eingabe){
    double answer=0; //Ausgabevariable
    QString Ausgabe;
    int temp=0;
    char input[300]; //Maximalmenge aller Zeichen der Eingabe
    char number_temp[300]; //Größtmögliche einzelne Zahl
    int used[5]; //Tempörär zum speichern der bereits genutzen Stellen im Array number
    float number[5]; //Array der Zahlen zum Rechnen
    char operation[5]; //Auch min. 5, weil operation[0] leer ist, zum einfacheren Rechnen
    char sorted[300]; // String für bereinigte Eingabe
    for(int i=0;i<6;i++){
        number[i]='\0';
        operation[i]='\0';
    }
    for(int i=0;i <301;i++){
        sorted[i]=' ';
        number_temp[i]=' ';
    }
    for(int i=0;i <300;i++){
        input[i]=' ';
    }
    operation[1]=' '; //Nötig, um bei Eingabe keiner Rechnung die Zahl auszugeben
    strcpy(input, eingabe.toStdString().c_str());    //Löschen der Leerzeichen
    int j=0;  //Hilf
    for(int i=0; input[i]; ++i){ //Geht den gesamten String durch
        if(input[i]!=' '){ //Falls keine Leerzeile:
            sorted[j++]=input[i]; //in den String sorted schreiben und die Stelle in sorted hochzählen
        }
    }
    sorted[j]=0; //Letztes Zeichen löschen
    char err[300];
    int neg = 1; //Hilfsvariable für negative Zahlen
    int x=1,k=0;
    strcpy(err,input);
    for(int i = 0; i < strlen(sorted); i++){
        if(isdigit(sorted[i]) || sorted[i] == '.'){
            strncat(number_temp, &sorted[i], 1); //zahl zusammensetzen
        }
        strcpy(input,err); //Kompensation des overflows..... (nicht schön!)
        if((sorted[i] == '-' && i == 0) || (sorted[i] == '-' && !isdigit(sorted[i-1]))){
            neg = -1; //falls Minus vorhanden, in einer Hilfsvariable speichern
            continue; //Durchgang beenden und mit nächstem i weiter. (sonst wird nichts mit Minus multipliziert, weil die nächste Schleife dies löschen würde)
        }
        if(sorted[i] == '+' || sorted[i] == '-' || sorted[i] == '*' || sorted[i] == '/' || sorted[i] == '^' || sorted[i] == '%'){
            number[k] = atof(number_temp) * neg; //number_temp in float umwandeln und mit dem Minus, falls vorhanden, multiplizieren
            neg = 1; //Minus wieder löschen
            strcpy(number_temp, ""); //number_temp leeren
            operation[x++] = sorted[i]; //den Operator an das Operator-Array übergeben
            k++; //Laufvariablen hochzählen, um auf die nächsten Stellen in den Arrays für die Zahlen und die Operatoren zu springen
        }
        number[k] = atof(number_temp) * neg; //Zahl im Array als Float abspeichern und Minus hinzufügen, falls letzte Zahl negativ (weil die Schleife dafür bei der letzten Zahl nicht mehr aufgerufen wird)
        // Der Teil ist wichtig, falls die letzte Zahl (nach dem letzten operator) negativ ist.
    }
    if(operation[1]== ' '){ //Übergeben der Eingabe an die Output bei keinem Operator (alternativ if mit 6 Argumenten - das hier ist kürzer)
        answer=number[0];
        Ausgabe = QString::number(answer);
        return Ausgabe;
    }
    for(int i=5; i>0; i--){ //Rechnungen mit höchstem Rang(3) von rechts (Potenzrechnung von rechts)
        if(operation[i]=='^'){ //Falls Potenz auftritt:
            number[i]=pow(number[i-1], number[i]); //Rechnung der Potenz
            number[i-1]=number[i]; //Zweiten Operanden überschreiben
            used[i]=1; //Hilfsvariable zum späteren Überschreiben der benutzten Stellen im Array
            used[i-1]=1; //Alle benutzten Stellen bekommen im used den Wert 1
            answer=number[i-1]; //rechnen mit der Variable answer, um eine temporäre Variable zu sparen
        }
    }
    for(int i=0; i<5; i++){ //Ebenfalls Rechnungen mit höchtem Rang(3), aber von links
        if(operation[i]=='%'){ //Falls Modulo auftritt:
            number[i]=fmod(number[i-1], number[i]); //Rechnung des Modulo
            number[i-1]=number[i]; //Zweiten Operanden überschreiben
            used[i]=1; //Hilfsvariable zum späteren Überschreiben der benutzten Stellen im Array
            used[i-1]=1; //Alle benutzten Stellen bekommen im used den Wert 1
            answer=number[i-1]; //rechnen mit der Variable answer, um eine temporäre Variable zu sparen
        }
    }
    for(int i=0; i<5; i++){ //Rechnungen mit Rang 2 (von links)
        if((operation[i]=='*')||(operation[i]=='/')){ //Falls Mal oder Geteilt auftritt:
            switch(operation[i]){ //Switch zum Auswählen der gewünschten Operator
            case '*': //Falls Mal:
                number[i-1]=number[i-1]*number[i]; // Mal rechnen
                break; //Switch beenden
            case '/': //Falls geteilt:
                if(number[i]==0){ //Prüfen, ob Teilen durch Null
                    return "ERROR_div_zero"; //Falls ja, die Error-Funktion ausführen, welche einen Fehler ausgibt und das Programm beendet
                }
                number[i-1]=number[i-1]/number[i]; //Geteilt rechnen
                break; //Switch beenden
            }
            number[i]=number[i-1]; //Zweiten Operanden überschreiben
            answer=number[i]; //rechnen mit der Variable answer, um eine temporäre Variable zu sparen
            used[i]=1; //Hilfsvariable zum späteren Überschreiben der benutzten Stellen im Array
            used[i-1]=1; //Alle benutzten Stellen bekommen im used den Wert 1
            temp=i; //Überschreiben aller bisher benutzten Stellen im Array der Zahlen mit dem Ergebnis dieser Rechnung:
            while(used[temp-1]==1 && (operation[temp]=='*'|| operation[temp]=='/' || operation[temp]=='^' || operation[temp]=='%')){
                number[temp-1]=answer; //setzt alle linken, direkt anschließenden und bereits benutzen Variablen auf den Wert der Rechnung
                temp--; //geht nach links
            }
            temp=i; //temp wird in der Schleife durchgezählt
            while(used[temp+1]==1 && (operation[temp+1]=='^' || operation[temp+1]=='%')){
                number[temp+1]=answer; //setzt alle rechten und im vorherigen Rang benutzten Variablen auf den Wert der Rechnung
                temp++; //geht nach rechts
            }
        }
    }
    for(int i=0; i<5; i++){ //Rechnungen mit Rang 1
        if(operation[i]=='+' || operation[i]=='-'){ //Prüft, ob Operationen des ersten Ranges vorhanden sind
            switch(operation[i]){ //Prüft, welche Operation vorhanden ist
            case '+': //Falls Addition vorhanden ist:
                number[i-1]=number[i-1]+number[i]; //Addieren
                break;
            case '-': //Falls Subtraktion vorhanden ist:
                number[i-1]=number[i-1]-number[i]; //Subtrahieren
                break;
            }
            number[i]=number[i-1]; //setzt den zweiten Wert gleich dem Ergebnis
            answer=number[i-1]; //setzt eine Hilfsvariable ebenfalls dem Ergebnis, um in den While-Schleifen damit zu arbeiten
            used[i]=1; //Speichern, dass mit der Variable bereits gerechnet wurde
            used[i-1]=1; //Speichern, dass mit der Variable bereits gerechnet wurde
            temp=i; //
            while(used[temp-1]==1 && (operation[temp]=='+' || operation[temp]=='-'  || operation[temp]=='*' || operation[temp]=='/' || operation[temp]=='^' || operation[temp]=='%')){
                number[temp-1]=answer; //setzt alle linken, direkt anschließenden und bereits benutzen Variablen auf den Wert der Rechnung
                temp--;
            }
            temp=i;
            while(used[temp+1]==1 && (operation[temp+1]=='*'|| operation[temp+1]=='/' || operation[temp+1]=='^' || operation[temp+1]=='%')){
                number[temp+1]=answer; //setzt alle rechten und im vorherigen Rang benutzten Variablen auf den Wert der Rechnung
                temp++;
            }
        }
    }
    Ausgabe = QString::number(answer);
    return Ausgabe;
   }

void Zeileneingabe::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->textEdit->setText(calculating(item->text()));
}
