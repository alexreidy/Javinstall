/* Javinstall class definition
** Manages download, extraction, installation, etc.
** Copyright (C) 2012 Alex Reidy
** License: MIT
*/

#include "javinstall.h"
#include <stdlib.h>
#include <fstream>

Javinstall::Javinstall() {
    Javinstall::password = "";
}

void Javinstall::set_choices(int version, QString arch) {
    Javinstall::version_choice = version;
    Javinstall::architecture = arch;
}

// Set operation equal to the specified task for the thread:
void Javinstall::set_op(QString task) {
    Javinstall::operation = task;
}

QString Javinstall::get_op() {
    return Javinstall::operation;
}

void Javinstall::setPass(QString pass) {
    Javinstall::password = pass;
}

void Javinstall::run() {
    if (Javinstall::operation == "download") {
        // Cookie information passed as the header is probably subject to change:
        QString header = "--header 'Cookie: gpw_e24=http%3A%2F%2Fwww.oracle.com%2Ftechnetwork%2Fjava%2Fjavase%2Fdownloads%2Fjre7-downloads-1637588.html' ";
        QString url;
        if (Javinstall::architecture == "32-bit") {
            switch(Javinstall::version_choice) {
                case 0: // JRE
                    url = "http://download.oracle.com/otn-pub/java/jdk/7u5-b06/jre-7u5-linux-i586.tar.gz";
                    break;
                case 1: // JDK
                    url = "http://download.oracle.com/otn-pub/java/jdk/7u5-b06/jdk-7u5-linux-i586.tar.gz";
                    break;
            }
        } else if (Javinstall::architecture == "64-bit")  {
            switch(Javinstall::version_choice) {
                case 0: // JRE
                    url = "http://download.oracle.com/otn-pub/java/jdk/7u5-b06/jre-7u5-linux-x64.tar.gz";
                    break;
                case 1: // JDK
                    url = "http://download.oracle.com/otn-pub/java/jdk/7u5-b06/jdk-7u5-linux-x64.tar.gz";
                    break;
            }
        }

        // Format and execute custom wget command to download:
        QString str_cmd = "wget --no-cookies " + header + url;
        system(str_cmd.toStdString().c_str());
    }

    if (Javinstall::operation == "extract") {
        QString fname;
        if (Javinstall::architecture == "32-bit") {
            switch(Javinstall::version_choice) {
                case 0: // JRE
                    fname = "jre-7u5-linux-i586.tar.gz";
                    break;
                case 1: // JDK
                    fname = "jdk-7u5-linux-i586.tar.gz";
                    break;
            }
        } else if (Javinstall::architecture == "64-bit")  {
            switch(Javinstall::version_choice) {
                case 0: // JRE
                    fname = "jre-7u5-linux-x64.tar.gz";
                    break;
                case 1: // JDK
                    fname = "jdk-7u5-linux-x64.tar.gz";
                    break;
            }
        }

        // Extract:
        QString str_cmd = "tar -xvf " + fname;
        system(str_cmd.toStdString().c_str());

    }

    if (Javinstall::operation == "install") {
        QString fname;
        if (Javinstall::architecture == "32-bit") {
            switch(Javinstall::version_choice) {
                case 0: // JRE
                    fname = "jre1.7.0_05";
                    break;
                case 1: // JDK
                    fname = "jdk1.7.0_05";
                    break;
            }
        } else if (Javinstall::architecture == "64-bit")  {
            switch(Javinstall::version_choice) {
                case 0: // JRE
                    fname = "jre1.7.0_05";
                    break;
                case 1: // JDK
                    fname = "jdk1.7.0_05";
                    break;
            }
        }

        QString str_cmd;

        QString pass = Javinstall::password;
        QString command = "echo " + pass + " | sudo -S ";

        if (Javinstall::version_choice == 0) { // JRE
            str_cmd = command + "mkdir /opt/jre";
            system(str_cmd.toStdString().c_str());

            str_cmd = command + "mv " + fname + "/* /opt/jre";

            // Move files to correct directory:
            system(str_cmd.toStdString().c_str());

            // Create a symbolic link to the java executable in a directory that's in the PATH:
            str_cmd = command + "ln -s /opt/jre/bin/java /usr/bin/java";
            system(str_cmd.toStdString().c_str());
        }

        if (Javinstall::version_choice == 1) { // JDK
            str_cmd = command + "mkdir /opt/jdk";
            system(str_cmd.toStdString().c_str());

            // Move files to correct directory:
            str_cmd = command + "mv " + fname + "/* /opt/jdk";
            system(str_cmd.toStdString().c_str());

            // Create a symbolic link to the javac & jar executables in a directory that's in the PATH:
            str_cmd = command + "ln -s /opt/jdk/bin/javac /usr/bin/javac";
            system(str_cmd.toStdString().c_str());
            str_cmd = command + "ln -s /opt/jdk/bin/jar /usr/bin/jar";
            system(str_cmd.toStdString().c_str());

        }

    }
    
    if (Javinstall::operation == "install_browser_plugin") {
		if (Javinstall:architecture == "32-bit")
			system("ln -s /opt/jre/lib/i386/libnpjp2.so /usr/lib/firefox/plugins/");
		
		if (Javinstall::architecture == "64-bit")
			system("ln -s /opt/jre/lib/amd64/libnpjp2.so /usr/lib/firefox/plugins/");
    }
}
