#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

// #include "registerdialog.h"
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_LoginBtn_clicked();
    void onRegisterClicked(const QString &link);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
