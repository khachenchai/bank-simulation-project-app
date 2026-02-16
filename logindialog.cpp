#include "logindialog.h"
#include "ui_logindialog.h"
#include "registerdialog.h"
#include <iostream>
using namespace std;

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    QPixmap pix(":/assets/assets/img/logo_resized2.png");
    // int w = ui->LogoLabel->width();
    int h = ui->LogoLabel->height();

    ui->LogoLabel->setPixmap(
        pix.scaled(
            480, h,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        )
    );

    ui->LogoLabel->setAlignment(Qt::AlignCenter);

    QAction *toggleEye = new QAction(this);
    toggleEye->setIcon(QIcon(":/assets/assets/eye_hide.png"));

    ui->PasswordEdit->addAction(toggleEye, QLineEdit::TrailingPosition);

    bool isPasswordVisible = false;

    connect(toggleEye, &QAction::triggered, this, [=]() mutable {
        isPasswordVisible = !isPasswordVisible;

        ui->PasswordEdit->setEchoMode(
            isPasswordVisible ? QLineEdit::Normal : QLineEdit::Password
        );

        toggleEye->setIcon(QIcon(
        isPasswordVisible
            ? ":/assets/assets/eye.png"
            : ":/assets/assets/eye_hide.png"
        ));
    });

    connect(ui->NoAcc, &QLabel::linkActivated, this, &LoginDialog::onRegisterClicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_LoginBtn_clicked()
{
    cout << "Login Btn Clicked";
    accept();

}

void LoginDialog::onRegisterClicked(const QString &link) {
    if (link == "register") {
        RegisterDialog dlg(this);
        close();
        dlg.exec();
        // this->close();
    }
}
