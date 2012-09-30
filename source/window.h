/* Window class declaration
** Manages primary UI and functionality
** Copyright (C) 2012 Alex Reidy
** License: MIT
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "getpass.h"
#include "about.h"
#include "help.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    
private slots:
    void when_thread_done();

    void on_actionHelp_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_installButton_clicked();

protected:
    Ui::Window *ui;

private:

    About about; // Declare an About form object
    Help help; // I need somebody help

    GetPass getPass;

};

#endif // WINDOW_H
