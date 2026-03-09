#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);

//     LoginDialog login;
//     if (login.exec() == QDialog::Accepted) {
//         MainWindow w;
//         w.show();
//         return a.exec();
//     }

// }

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);

//     while (true)
//     {
//         LoginDialog login;

//         if (login.exec() != QDialog::Accepted)
//             break;

//         MainWindow w;

//         QObject::connect(&w, &MainWindow::logoutRequested,
//                          [&]() {
//                              // จะทำให้ loop กลับไป login ใหม่
//                          });

//         w.show();

//         a.exec();   // รอจน window ปิด
//     }

//     return 0;
// }

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
