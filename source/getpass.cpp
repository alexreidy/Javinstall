#include "getpass.h"
#include "ui_getpass.h"

GetPass::GetPass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetPass)
{
    ui->setupUi(this);
}

GetPass::~GetPass()
{
    delete ui;
}

// Allows the Window object access to password:
QString GetPass::get_pass() {
    return GetPass::password;
}

void GetPass::on_buttonBox_accepted()
{
    GetPass::password = ui->lineEdit->text();
}

void GetPass::on_buttonBox_rejected()
{
    qApp->quit();
}
