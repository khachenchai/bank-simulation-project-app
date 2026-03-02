#include "transferdialog.h"
#include "ui_transferdialog.h"
#include "backend/user.h"

TransferDialog::TransferDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransferDialog)
{
    ui->setupUi(this);

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

