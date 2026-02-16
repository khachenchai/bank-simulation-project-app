#include "registerdialog.h"
#include "logindialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    connect(ui->ToLogin, &QLabel::linkActivated, this, &RegisterDialog::onLoginClicked);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::onLoginClicked(const QString &link) {
    if (link == "login") {
        LoginDialog dlg(this);
        close();
        dlg.exec();
    }
}
