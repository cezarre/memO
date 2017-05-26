#ifndef GETSTDOUTFROMCOMMAND_H
#define GETSTDOUTFROMCOMMAND_H

#include <string>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QCloseEvent>
#include <QMessageBox>
#include <string>
#include <algorithm>


class GetStdoutFromCommand
{
public:
    GetStdoutFromCommand();
    std::string Execute(std::string cmd);
};

#endif // GETSTDOUTFROMCOMMAND_H
