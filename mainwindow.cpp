#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRegularExpression>>

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subtTrigger = false;
bool clearTrigger = false;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //checks to see if 0.0 is displayed on startup
    ui->Display->setText(QString::number(calcVal));
    //creates array to ref all keys to push buttons
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Equal, SIGNAL(released()), this,
            SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeSign()));
    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ClearAll()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//functions for handling all numeric buttons
void MainWindow::NumPressed() {
    QPushButton *button  = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)) {
        ui->Display->setText(butVal);
    } else {
        QString newVal =  displayVal + butVal;
        double  dblNewVal =  newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

//Function for handling operations buttons
void MainWindow::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subtTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal  = displayVal.toDouble();
    QPushButton *button  =(QPushButton *)sender();;
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else {
        subtTrigger = true;
    }
    ui->Display->setText("");
}

//Function for handling Equal Button
void MainWindow::EqualButton(){
    double  solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subtTrigger || divTrigger || multTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if (subtTrigger){
            solution = calcVal - dblDisplayVal;
        } else if (multTrigger){
            solution = calcVal * dblDisplayVal;
        } else {
            solution = calcVal / dblDisplayVal;
        }
    }

    ui->Display->setText(QString::number(solution));
}

//Function for handling changinng signs buttton
void MainWindow::ChangeNumSign()  {
    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    if (match.hasMatch()) {
        double dblDisplayVal = displayVal.toDouble();
        double  dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

// Function for handling clear all button
void MainWindow::ClearAll() {
    clearTrigger = false;
    if(clearTrigger){
        clearTrigger = true;
    }
    ui->Display->setText("0");




}
