#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QCloseEvent>
#include <QMessageBox>
#include <string>
#include <algorithm>
#include <math.h>
#include <sstream>
#include <iomanip>

int unit;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{




    ui->setupUi(this);

    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutBox()));


        if(QSystemTrayIcon::isSystemTrayAvailable() == false)
        {
            std::cerr << "This application is not available on this computer.";
            QCoreApplication::quit();
        }
        else
        {
            std::cout << "OK";
        }




        prefrencesAction = new QAction(tr("Pref&rences"),this);
        connect(prefrencesAction,SIGNAL(triggered()),this,SLOT(showNormal()));

        quitAction = new QAction(tr("&Quit"),this);
        connect(quitAction,SIGNAL(triggered()),this,SLOT(quitAppPrompt()));


        trayIconMenu = new QMenu(this);

        trayIconMenu->addAction(prefrencesAction);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(quitAction);


        trayIcon = new QSystemTrayIcon(this);
        trayIcon->setContextMenu(trayIconMenu);


        connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


        trayIcon->setIcon(this->windowIcon());
        trayIcon->show();




}

void MainWindow::aboutBox() {
    QMessageBox::about(this, "About", "Created by Cezary Olkowski");

}

void MainWindow::quitAppPrompt() {


    QMessageBox::StandardButton quitBtn = QMessageBox::question( 0, "memO",
                                                                "Quit memO?",
                                                                QMessageBox::Yes | QMessageBox::No);


    if (quitBtn != QMessageBox::Yes) {
        return;
    }
    QCoreApplication::quit();

}


void MainWindow::closeEvent (QCloseEvent *event)
{
    event->ignore();
    this->hide();

}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::MiddleClick:
        this->showMinimized();
        break;
    case QSystemTrayIcon::Trigger:
        this->notifySend();
        break;
    default:
        ;

    }
}

void MainWindow::notifySend() {
    try
    {

        GetStdoutFromCommand comm;
        std::string catMemFree = "cat /proc/meminfo | grep 'MemFree'";
        std::string memFree = comm.Execute(catMemFree);


        memFree.erase(std::remove_if(memFree.begin(), memFree.end(), isalpha), memFree.end() );
        memFree.erase(std::remove_if(memFree.begin(), memFree.end(), isspace), memFree.end() );
        memFree.erase(std::remove(memFree.begin(), memFree.end(), ':'), memFree.end() );


        int in_spec_unit = std::stoi(memFree);
        std::string unitString = "";
        std::string qString = "";

        if (ui->UnitComboBox->currentText() == "kB")
        {
            qString = memFree;
            unitString = "kB";
        }
        else if (ui->UnitComboBox->currentText() == "MB")
        {
            in_spec_unit = in_spec_unit/(1024);
            qString = std::to_string(in_spec_unit);
            unitString = "MB";
        }
        else if (ui->UnitComboBox->currentText() == "GB")
        {

            float in_spec_unit_f = (float)in_spec_unit/(1024*1024);
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << in_spec_unit_f;
            qString = stream.str();
            unitString = "GB";

        }
        else
        {
            in_spec_unit = 0;
            unitString = "ERROR";
        }





        std::string command = "notify-send \"Free memory: " + qString + unitString + "\"";

        system(command.c_str());

    }
    catch(int e)
    {
        std::cerr << "NaN " << e << std::endl;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
