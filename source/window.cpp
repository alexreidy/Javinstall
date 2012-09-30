#include "window.h"
#include "ui_window.h"
#include "javinstall.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

Javinstall javin;

// On button click, install chosen Java software:
void Window::on_installButton_clicked()
{
    Window::getPass.setWindowTitle("Grant Javinstall root access");
    Window::getPass.show();
    Window::getPass.activateWindow();
    Window::getPass.raise();

    int version_choice = ui->installchoice_combobox->currentIndex();
    QString architecture = "none";

    if (ui->radio_32->isChecked()) {
        architecture = "32-bit";
        ui->statusLabel->setText("Status");
    } else if (ui->radio_64->isChecked()) {
        architecture = "64-bit";
        ui->statusLabel->setText("Status");
    } else {
        ui->statusLabel->setText("Choose architecture (32 or 64 bit)");
    }

    if (architecture != "none") {
        ui->installButton->setEnabled(false);
        javin.set_choices(version_choice, architecture);
        connect(&javin, SIGNAL(finished()), this, SLOT(when_thread_done()));
        javin.set_op("download");
        javin.start();
        ui->progressBar->setValue(5);
        ui->statusLabel->setText("Downloading...");
    }

}

void Window::when_thread_done() {
    // Reverse the chronological order of if-statements to prevent running more than one.
    if (javin.get_op() == "install") {
        ui->progressBar->setValue(100);
        ui->statusLabel->setText("Done.");
        ui->installButton->setEnabled(true);
    }

    if (javin.get_op() == "extract") {
        ui->progressBar->setValue(80);
        ui->statusLabel->setText("Done extracting - installing...");
        javin.set_op("install");
        javin.start();
        // Set the password variable in the Javinstall class:
        javin.setPass(Window::getPass.get_pass());
    }

    if (javin.get_op() == "download") {
        ui->progressBar->setValue(50);
        ui->statusLabel->setText("Download complete - extracting...");
        javin.set_op("extract");
        javin.start();
    }
}

// Exit if menu->quit is selected:
void Window::on_actionQuit_triggered()
{
    qApp->exit();
}

// Show about window:
void Window::on_actionAbout_triggered()
{
    Window::about.setWindowTitle("About");
    Window::about.show();
    Window::about.activateWindow();
    Window::about.raise();
}

void Window::on_actionHelp_triggered()
{
    Window::help.setWindowTitle("Help");
    Window::help.show();
    Window::help.activateWindow();
    Window::help.raise();
}
