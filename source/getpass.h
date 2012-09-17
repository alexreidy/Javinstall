#ifndef GETPASS_H
#define GETPASS_H

#include <QDialog>

namespace Ui {
class GetPass;
}

class GetPass : public QDialog
{
    Q_OBJECT
    
public:
    explicit GetPass(QWidget *parent = 0);
    ~GetPass();

    QString get_pass();
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::GetPass *ui;
    QString password;
};

#endif // GETPASS_H
