#include "transferdialog.h"
#include "ui_transferdialog.h"
#include "backend/user.h"
#include "confirmtransactiondialog.h"
#include <QMessageBox>

using TransactionType = ConfirmTransactionDialog::TransactionType;

TransferDialog::TransferDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransferDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    User user;

    QString userId = user.currentUser().getUserId();
    ui->UserIdLabel->setText(userId);

    double amount = user.currentUser().getBalance();
    ui->BalanceLabel->setText(QString::number(amount, 'f', 2) + " บาท");

}

TransferDialog::~TransferDialog()
{
    delete ui;
}


void TransferDialog::on_SubmitBtn_clicked()
{
    QString selectBank = ui->BankCombo->currentText();
    QString recieverId = ui->UserIdEdit->text();
    QString balanceText = ui->BalanceEdit->text();

    if (balanceText.toDouble() <= 0 || balanceText.toDouble() > User::currentUser().getBalance() || balanceText.toDouble() > 150000) {
        QMessageBox::critical(
            this,
            "Transaction Failed",
            "กรุณากรอกจำนวนเงินให้ถูกต้อง"
            );

        return;
    }
    ConfirmTransactionDialog dlg(
        TransactionType::Transfer,
        "Mhee Bank",
        selectBank,
        recieverId,
        balanceText.toDouble()
    );

    if (dlg.exec() == QDialog::Accepted) {
        accept();
    }
}

