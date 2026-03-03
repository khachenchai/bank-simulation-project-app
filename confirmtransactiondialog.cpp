#include "confirmtransactiondialog.h"
#include "ui_confirmtransactiondialog.h"

ConfirmTransactionDialog::ConfirmTransactionDialog(TransactionType type, QString fromBank, double balance, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmTransactionDialog)
{
    ui->setupUi(this);
    setupUIByType();
}

ConfirmTransactionDialog::~ConfirmTransactionDialog()
{
    delete ui;
}

void ConfirmTransactionDialog::setupUIByType() {
    if (m_type == TransactionType::TopUp) {
        ui->Title->setText("ยืนยันการเติมเงิน");
        ui->ToTitle->hide();
        ui->ToLineEdit->hide();
        ui->FromLineEdit->setText(fromBank);
        ui->ToLineEdit->setText("Mhee Bank");
        ui->BalanceText->setText(QString::number(balance, 'f', 2) + " บาท");

    } else if (m_type == TransactionType::Transfer) {
        ui->Title->setText("ยืนยันการโอนเงิน");
        ui->ToTitle->show();
        ui->ToLineEdit->show();
    }
}
