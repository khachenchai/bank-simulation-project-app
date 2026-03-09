#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool logout = false;

    do
    {
        LoginDialog login;

        if (login.exec() != QDialog::Accepted)
            break;

        MainWindow w;

        logout = false;

        QObject::connect(&w, &MainWindow::logoutRequested, [&]() {
            logout = true;
            w.close();
        });

        w.show();

        a.exec();

    } while (logout);

    return 0;
}
