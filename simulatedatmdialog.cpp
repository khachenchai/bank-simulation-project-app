#include "simulatedatmdialog.h"
#include "ui_simulatedatmdialog.h"
#include <QMessageBox>
#include "backend/transaction.h"

SimulatedATMDialog::SimulatedATMDialog(QString otpStr, double balance, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SimulatedATMDialog),
    m_otpStr(otpStr),
    m_balance(balance)
{
    ui->setupUi(this);

}

SimulatedATMDialog::~SimulatedATMDialog()
{
    delete ui;
}

void SimulatedATMDialog::on_ConfirmBtn_clicked()
{
    QString otpInput = ui->OTPEdit->text();

    if (otpInput.isEmpty()) {
        QMessageBox::critical(
            this,
            "Transaction Failed",
            "กรุณากรอก OTP"
            );

        return;
    } else if (otpInput != m_otpStr) {
        QMessageBox::critical(
            this,
            "Transaction Failed",
            "ไม่พบรหัส OTP นี้"
            );

        return;
    }

    Transaction transaction;

    bool isWithdrawSuccess = transaction.withdrawFunc(m_balance);

    if (!isWithdrawSuccess) {
        QMessageBox::critical(
            this,
            "Transaction Failed",
            "เกิดข้อผิดพลาด"
            );

        return;
    }

    QString text = "ถอนเงินเป็นจำนวน" + QString::number(m_balance, 'f', 2) + " บาท เรียบร้อย";

    QMessageBox::information(
        this,
        "Transaction Success",
        text
        );

    accept();
}

