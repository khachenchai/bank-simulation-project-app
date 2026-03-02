#include "transferdialog.h"
#include "ui_transferdialog.h"

TransferDialog::TransferDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransferDialog)
{
    ui->setupUi(this);

    QString userId = user.currentUser().getUserId();
    ui->UserIdLabel->setText(userId);

    double amount = user.currentUser().getBalance();
    ui->BalanceLabel->setText(QString::number(amount));

}

TransferDialog::~TransferDialog()
{
    delete ui;
}

