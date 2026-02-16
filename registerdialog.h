#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

// #include "logindialog.h"
#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void onLoginClicked(const QString &link);

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
