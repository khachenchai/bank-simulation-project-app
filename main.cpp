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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    while (true)
    {
        LoginDialog login;

        if (login.exec() != QDialog::Accepted)
            break;

        MainWindow w;

        QObject::connect(&w, &MainWindow::logoutRequested,
                         [&]() {
                             // จะทำให้ loop กลับไป login ใหม่
                         });

        w.show();

        a.exec();   // รอจน window ปิด
    }

    return 0;
}
