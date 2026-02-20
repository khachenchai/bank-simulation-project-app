#include "registerdialog.h"
#include "logindialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#include "helper.h"

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

void RegisterDialog::on_RegisterBtn_clicked()
{
    // validation
    std::vector<QString> errors;
    QString prefix = ui->prefixEdit->currentText(), gender = ui->genderEdit->currentText();
    QString fname = ui->firstnameEdit->text(), lname = ui->lastnameEdit->text(), tel = ui->telEdit->text(), ctzId = ui->ctzIdEdit->text();
    QString password = ui->passwordEdit->text(), passwordConfirm = ui->confirmPasswordEdit->text();

    if (prefix.isEmpty() || fname.isEmpty() || lname.isEmpty()) errors.push_back("กรุณากรอกคำนำหน้า ชื่อจริง นามสกุล ให้ถูกต้อง");
    if (ctzId.isEmpty() || ctzId.size() != 13 || !Helper::checkIsNumerial(ctzId)) errors.push_back("กรุณากรอกเลขบัตรประจำตัวประชาชนให้ถูกต้อง");
    if (tel.isEmpty() || !Helper::checkIsNumerial(tel)) errors.push_back("กรุณากรอกเบอร์โทรศัพท์ให้ถูกต้อง");
    if (gender.isEmpty()) errors.push_back("กรุณาระบุเพศ");
    if (password.isEmpty() || password.size() != 6 || !Helper::checkIsNumerial(password)) errors.push_back("กรุณากรอกตัวเลขรหัสผ่าน 6 ตัวให้ถูกต้อง");
    if (password != passwordConfirm) errors.push_back("กรุณากรอกยืนยันรหัสผ่านให้ตรงกับช่องรหัสผ่าน");

    if (errors.size() > 0) {
        QString errorsText = "";
        for (int i = 0; i < errors.size(); i++) {
            errorsText += errors[i];
            errorsText += '\n';
        }
        QMessageBox::warning(this, "Mhee Bank", errorsText);
    } else {
        // register func [Fuji's Real Backend Code Here]

        LoginDialog dlg(this);
        dlg.exec();
        this->close();

    }
}

