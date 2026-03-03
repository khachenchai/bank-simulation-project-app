#include "confirmtransactiondialog.h"
#include "ui_confirmtransactiondialog.h"
#include <QDebug>
#include "backend/user.h"
#include "backend/transaction.h"
#include <QMessageBox>

ConfirmTransactionDialog::ConfirmTransactionDialog(TransactionType type, QString fromBank, QString toBank, QString targetUserId, double balance, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmTransactionDialog),
    m_type(type),
    m_fromBank(fromBank),
    m_toBank(toBank),
    m_targetUserId(targetUserId),
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
        ui->FromLineEdit->setText(m_fromBank);
        ui->ToLineEdit->setText(m_toBank);
        ui->BalanceText->setText(QString::number(m_balance, 'f', 2) + " บาท");


    }
}

void ConfirmTransactionDialog::on_ConfirmBtn_clicked()
{
    QString passwordInput = ui->PasswordEdit->text();

    User& user = User::currentUser();

    if (!user.verifyPassword(passwordInput, user.getSalt())) {

        QMessageBox::warning(
            this,
            "Login Failed",
            "Incorrect password. Please try again."
            );

        return;
    }

    Transaction transaction;

    if (m_type == TransactionType::TopUp) {
        bool isTopupSuccess =
            transaction.topupFunc(m_fromBank, m_balance);

        if (!isTopupSuccess) {

            QMessageBox::critical(
                this,
                "Transaction Failed",
                "Top up failed. Please try again."
                );

            return;
        }

        QMessageBox::information(
            this,
            "Success",
            "Top up completed successfully."
            );

        accept();
    } else if (m_type == TransactionType::Transfer) {
        bool isTransferSuccess =
            transaction.transferFunc(
                m_targetUserId,
                m_toBank,
                m_balance
                );

        if (!isTransferSuccess) {

            QMessageBox::critical(
                this,
                "Transaction Failed",
                "Transfer failed. Please check the information and try again."
                );

            return;
        }

        QMessageBox::information(
            this,
            "Success",
            "Transfer completed successfully."
            );

        accept();
    }
}

