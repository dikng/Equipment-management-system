#include "mainwindow.h"
#include "loginwindow.h"
#include <admin.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/ICO/soft.ico"));

    LoginWindow login;
    login.show();
    if(login.exec() == QDialog::Accepted){
        MainWindow mainWindow;
        mainWindow.show();
        return a.exec();
    }
    else {
        return 0;
    }
/*    MainWindow m;
    qRegisterMetaType<Admin>();
    m.show();
    return a.exec();*/
}
