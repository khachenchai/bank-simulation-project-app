#include "confirmtransactiondialog.h"
#include "ui_confirmtransactiondialog.h"
#include <QDebug>
#include "backend/user.h"
#include "backend/transaction.h"
#include <QMessageBox>
#include "confirmwithdrawdialog.h"
#include "helper.h"
// #include "simulatedatmdialog.h"

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
        ui->InputBalanceEdit->hide();
        ui->InputBalanceTitle->hide();
        ui->FromLineEdit->setText(m_fromBank);
        ui->ToLineEdit->setText("Mhee Bank");
        ui->BalanceText->setText(QString::number(m_balance, 'f', 2) + " บาท");

    } else if (m_type == TransactionType::Transfer) {
        ui->Title->setText("ยืนยันการโอนเงิน");
        ui->ToTitle->show();
        ui->ToLineEdit->show();
        ui->InputBalanceEdit->hide();
        ui->InputBalanceTitle->hide();
        ui->FromLineEdit->setText(m_fromBank + " - " + User::currentUser().getFullname());
        ui->ToLineEdit->setText(m_toBank == "Mhee Bank" ? m_toBank + " - " + User::getFullnameByUserId(m_targetUserId) : m_toBank);
        ui->BalanceText->setText(QString::number(m_balance, 'f', 2) + " บาท");
    } else if (m_type == TransactionType::Withdraw) {
        ui->Title->setText("ยืนยันการถอนเงิน");
        ui->ToTitle->hide();
        ui->ToLineEdit->hide();
        ui->InputBalanceEdit->show();
        ui->InputBalanceTitle->show();
        ui->FromLineEdit->hide();
        ui->ToLineEdit->hide();
        ui->BalanceText->hide();
        ui->FromTitle->hide();
        ui->BalanceLabel->hide();
    }
}

void ConfirmTransactionDialog::on_ConfirmBtn_clicked()
{
    QString passwordInput = ui->PasswordEdit->text();

    User& user = User::currentUser();

    if (!user.verifyPassword(passwordInput, user.getSalt())) {

        QMessageBox::critical(
            this,
            "Login Failed",
            "Incorrect password. Please try again."
            );

        return;
    }

    qDebug() << "m_balance: " << m_balance;
    // qDebug() << "m_balance: " << ;

    if (m_balance <= 0) {
        QMessageBox::critical(
            this,
            "Transaction Failed",
            "กรุณากรอกจำนวนเงินให้ถูกต้อง"
            );

        return;
    }

    // ui->InputBalanceEdit->text().toDouble()

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

        if (m_balance <= 0) {
            QMessageBox::critical(
                this,
                "Transaction Failed",
                "กรุณากรอกจำนวนเงินให้ถูกต้อง"
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

        if (m_balance <= 0) {
            QMessageBox::critical(
                this,
                "Transaction Failed",
                "กรุณากรอกจำนวนเงินให้ถูกต้อง"
                );

            return;
        }

        QMessageBox::information(
            this,
            "Success",
            "Transfer completed successfully."
            );

        accept();
    } else if (m_type == TransactionType::Withdraw) {
        QString otpStr = Helper::generateOTP();
        double balance = ui->InputBalanceEdit->text().toDouble();

        qDebug() << "balance: " << balance;

        if (balance <= 0 || balance > User::currentUser().getBalance()) {
            QMessageBox::critical(
                this,
                "Transaction Failed",
                "กรุณากรอกจำนวนเงินให้ถูกต้อง"
                );

            return;
        }

        ConfirmWithdrawDialog dlg(otpStr, balance, this);
        if (dlg.exec() == QDialog::Accepted) {
            accept();
        }
    }
}

