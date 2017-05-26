#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include "getstdoutfromcommand.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    ~MainWindow();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void notifySend();
    void quitAppPrompt();
    void aboutBox();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon * trayIcon;
    QMenu * trayIconMenu;

    QAction *minimizeAction;    // minimalizowanie okna
    QAction *cur_mem;    // maksymalizowanie okna
    QAction *prefrencesAction;       // pokazanie okna
    QAction *quitAction;        // wyjście z aplikacji
};

#endif // MAINWINDOW_H
