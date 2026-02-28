#include "logindialog.h"
#include "ui_logindialog.h"
#include "registerdialog.h"
#include <QMessageBox>
#include <QWidget>
#include "helper.h"
#include <QVector>
#include <QDebug>

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
    QVector<QString> errors;
    QString ctzId = ui->CtzIdEdit->text();
    QString password = ui->PasswordEdit->text();

    // validation
    if (ctzId.isEmpty() || ctzId.size() != 13 || !Helper::checkIsNumerial(ctzId)) errors.push_back("กรุณากรอกเลขบัตรประจำตัวประชาชนให้ถูกต้อง");
    if (password.isEmpty() || password.size() != 6 || !Helper::checkIsNumerial(password)) errors.push_back("กรุณากรอกตัวเลขรหัสผ่าน 6 ตัวให้ถูกต้อง");

    if (errors.size() > 0) {
        QString errorsText = "";
        for (int i = 0; i < errors.size(); i++) {
            errorsText += errors[i];
            errorsText += '\n';
        }
        QMessageBox::warning(this, "Mhee Bank", errorsText);
    } else {
        // login func [Backend Func Here]

        qDebug() << "Login Btn Clicked";
        accept();
    }

}

void LoginDialog::onRegisterClicked(const QString &link) {
    if (link == "register") {
        RegisterDialog dlg(this);
        close();
        dlg.exec();
        // this->close();
    }
}
