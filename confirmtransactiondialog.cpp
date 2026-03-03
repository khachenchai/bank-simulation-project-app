#include "confirmtransactiondialog.h"
#include "ui_confirmtransactiondialog.h"
#include <QDebug>
#include "backend/user.h"
#include "backend/transaction.h"

ConfirmTransactionDialog::ConfirmTransactionDialog(TransactionType type, QString fromBank, double balance, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmTransactionDialog),
    m_type(type),
    m_fromBank(fromBank),
    m_balance(balance)
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
        ui->FromLineEdit->setText(m_fromBank);
        ui->ToLineEdit->setText("Mhee Bank");
        ui->BalanceText->setText(QString::number(m_balance, 'f', 2) + " บาท");

    } else if (m_type == TransactionType::Transfer) {
        ui->Title->setText("ยืนยันการโอนเงิน");
        ui->ToTitle->show();
        ui->ToLineEdit->show();
    }
}

void ConfirmTransactionDialog::on_ConfirmBtn_clicked()
{
    QString passwordInput = ui->PasswordEdit->text();
    User user = User::currentUser();
    if (user.verifyPassword(passwordInput, user.getSalt())) {
        qDebug() << "Salt: " << user.getSalt();
        

        bool isTopupSuccess = Transaction::topupFunc(m_frombank , m_balance);
        if (!isTopupSuccess) {
            qDebug() << "Sth is Failed";
        }

        qDebug() << "Success";

    } else {
        qDebug() << "Failed";
    }
}

