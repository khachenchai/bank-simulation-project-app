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

QString oriStyle = "padding: 4px;\nbackground: white;\nfont-size: 18px;\nborder-radius: 18px;\nborder: 2px solid #009E2A;\ncolor: #009E2A;\n";
QString selectedStyle = "padding: 4px;\nbackground: #009E2A;\nfont-size: 18px;\nborder-radius: 18px;\nborder: 2px solid #009E2A;\ncolor: white;\n";

void TopUpDialog::resetTopUpButtons()
{

    ui->Top100->setStyleSheet(oriStyle);
    ui->Top300->setStyleSheet(oriStyle);
    ui->Top500->setStyleSheet(oriStyle);
    ui->Top1000->setStyleSheet(oriStyle);
    ui->Top2000->setStyleSheet(oriStyle);
}

void TopUpDialog::on_Top100_clicked()
{
    resetTopUpButtons();
    ui->amountEdit->setText("100");
    ui->Top100->setStyleSheet(selectedStyle);
}


void TopUpDialog::on_Top300_clicked()
{
    resetTopUpButtons();
    ui->amountEdit->setText("300");
    ui->Top300->setStyleSheet(selectedStyle);
}


void TopUpDialog::on_Top500_clicked()
{
    resetTopUpButtons();
    ui->amountEdit->setText("500");
    ui->Top500->setStyleSheet(selectedStyle);
}


void TopUpDialog::on_Top1000_clicked()
{
    resetTopUpButtons();
    ui->amountEdit->setText("1000");
    ui->Top1000->setStyleSheet(selectedStyle);
}


void TopUpDialog::on_Top2000_clicked()
{
    resetTopUpButtons();
    ui->amountEdit->setText("2000");
    ui->Top2000->setStyleSheet(selectedStyle);
}

