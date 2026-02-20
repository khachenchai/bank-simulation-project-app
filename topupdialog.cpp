#include "topupdialog.h"
#include "ui_topupdialog.h"
#include "confirmtransactiondialog.h"
using TransactionType = ConfirmTransactionDialog::TransactionType;

TopUpDialog::TopUpDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TopUpDialog)
{
    ui->setupUi(this);
}

TopUpDialog::~TopUpDialog()
{
    delete ui;
}

void TopUpDialog::on_ConfirmBtn_clicked()
{
    ConfirmTransactionDialog dlg(TransactionType::TopUp, this);
    dlg.exec();
}

