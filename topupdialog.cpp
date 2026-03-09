#include "topupdialog.h"
#include "ui_topupdialog.h"
#include "confirmtransactiondialog.h"
#include <QMessageBox>
using TransactionType = ConfirmTransactionDialog::TransactionType;

static QString selectedBank = "";

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

void TopUpDialog::on_ConfirmBtn_clicked() {
    QString balanceText = ui->amountEdit->text().trimmed();
    double balance = balanceText.toDouble();

    qDebug() << "balance: " << balance;

    if (balance <= 0 || balance > 150000) {
        QMessageBox::critical(
            this,
            "Transaction Failed",
            "กรุณากรอกจำนวนเงินให้ถูกต้อง"
            );

        return;
    }

    if (selectedBank.isEmpty()) {
        QMessageBox::critical(
            this,
            "Transaction Failed",
            "กรุณาระบุธนาคาร"
            );

        return;
    }

    ConfirmTransactionDialog dlg(
        TransactionType::TopUp,
        selectedBank,
        "",
        "",
        balance,
        this
        );

    if (dlg.exec() == QDialog::Accepted) {
        accept();
    }
}

QString oriStyleAmountBtn = "padding: 4px;\nbackground: white;\nfont-size: 18px;\nborder-radius: 18px;\nborder: 2px solid #009E2A;\ncolor: #009E2A;\n";
QString selectedStyleAmountBtn = "padding: 4px;\nbackground: #009E2A;\nfont-size: 18px;\nborder-radius: 18px;\nborder: 2px solid #009E2A;\ncolor: white;\n";
QString oriStyleBtn = "QPushButton {""border: 4px solid #009E2A;""border-radius: 20px;""background: white;""font-size: 30px;""color: #484848;""padding: 10px;""}""QPushButton:hover {""background: #EEFBF0;""}";
QString selectedStyleBankBtn =
"QPushButton {"
"border: 4px solid #009E2A;"
"border-radius: 20px;"
"background: #009E2A;"
"font-size: 30px;"
"color: white;"
"padding: 10px;"
"}";

void TopUpDialog::resetBankButtons(){
    ui->BankABtn->setStyleSheet(oriStyleBtn);
    ui->BankBBtn->setStyleSheet(oriStyleBtn);
}

void TopUpDialog::resetTopUpButtons()
{
    ui->Top100->setStyleSheet(oriStyleAmountBtn);
    ui->Top300->setStyleSheet(oriStyleAmountBtn);
    ui->Top500->setStyleSheet(oriStyleAmountBtn);
    ui->Top1000->setStyleSheet(oriStyleAmountBtn);
    ui->Top2000->setStyleSheet(oriStyleAmountBtn);
}

void TopUpDialog::on_Top100_clicked()
{
    resetTopUpButtons();
    ui->amountEdit->setText("100");
    ui->Top100->setStyleSheet(selectedStyleAmountBtn);
}


void TopUpDialog::on_Top300_clicked()
{
    resetTopUpButtons();
    ui->amountEdit->setText("300");
    ui->Top300->setStyleSheet(selectedStyleAmountBtn);
}


void TopUpDialog::on_Top500_clicked()
{
    resetTopUpButtons();
    ui->amountEdit->setText("500");
    ui->Top500->setStyleSheet(selectedStyleAmountBtn);
}


void TopUpDialog::on_Top1000_clicked()
{
    resetTopUpButtons();
    ui->amountEdit->setText("1000");
    ui->Top1000->setStyleSheet(selectedStyleAmountBtn);
}


void TopUpDialog::on_Top2000_clicked()
{
    resetTopUpButtons();
    ui->amountEdit->setText("2000");
    ui->Top2000->setStyleSheet(selectedStyleAmountBtn);
}


void TopUpDialog::on_BankABtn_clicked()
{
    resetBankButtons();
    ui->BankABtn->setStyleSheet(selectedStyleBankBtn);
    selectedBank = "Bank A";
}


void TopUpDialog::on_BankBBtn_clicked()
{
    resetBankButtons();
    ui->BankBBtn->setStyleSheet(selectedStyleBankBtn);
    selectedBank = "Bank B";
}

