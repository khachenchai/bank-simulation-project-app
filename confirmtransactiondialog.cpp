#include "confirmtransactiondialog.h"
#include "ui_confirmtransactiondialog.h"

ConfirmTransactionDialog::ConfirmTransactionDialog(TransactionType type, QWidget *parent)
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
    } else if (m_type == TransactionType::Transfer) {
        ui->Title->setText("ยืนยันการโอนเงิน");
        ui->ToTitle->show();
        ui->ToLineEdit->show();
    }
}
