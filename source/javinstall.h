#ifndef JAVINSTALL_H
#define JAVINSTALL_H

#include "window.h"
#include <QThread>

class Javinstall : public QThread
{
    Q_OBJECT
signals:
    // ...
public:
    Javinstall();

    void set_choices(int version, QString arch);
    void run(); // Execute a process in a separate thread depending on specified operation

    void set_op(QString task); // Set operation
    QString get_op();

    void setPass(QString pass);

private:
    QString password; // User password
    int version_choice; // JDK/JRE = 0/1
    QString architecture; // 32 or 64-bit
    QString operation; // Task for thread to carry out

};

#endif // JAVINSTALL_H
