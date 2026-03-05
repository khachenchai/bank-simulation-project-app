#include "backend/user.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include "transactionitem.h"
#include "topupdialog.h"
#include "transferdialog.h"
#include "backend/transaction.h"
#include "confirmtransactiondialog.h"
#include <QDebug>
#include "helper.h"
#include "logindialog.h"

using TransactionType = ConfirmTransactionDialog::TransactionType;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Mhee Bank");

    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(35);
    shadow->setOffset(0, 6);
    shadow->setColor(QColor(0, 158, 42, 80));

    ui->BalanceLabel->setGraphicsEffect(shadow);

    User user;

    QString fname = user.currentUser().getFirstname();
    ui->NameTitle->setText("สวัสดี, " + fname);

    QString userId = user.currentUser().getUserId();
    ui->UserIdLabel->setText("หมายเลขบัญชี : " + userId);

    double amount = user.currentUser().getBalance();
    ui->BalanceLabel->setText(QString::number(amount, 'f', 2));

    Transaction transaction;

    QVector<TransactionRecord> list = transaction.getMyTransactions();

    QLayout *layout = ui->ScrollAreaOfHistory->layout();

    while (QLayoutItem* child = layout->takeAt(0)) {
        delete child->widget();
        delete child;
    }

    if (list.size() > 0) {
        ui->NoHistoryText->hide();
        ui->ScrollAreaOfHistory->show();
        for (const auto& t : std::as_const(list)) {
            TransactionItem *item = new TransactionItem(this);

            QString title;

            if (t.type == "transfer") {
                if (t.fromId == User::currentUser().getUserId())
                    title = "โอน";
                else
                    title = "รับเงิน";
            } else if (t.type == "topup") {

                title = "เติม";

            } else if (t.type == "withdraw") {

                title = "ถอน";

            } else {

                title = t.type;
            }

            // QString formattedDT = Helper::formatThaiDateTime(t.dateTime);

            qDebug() << "t.toId: " << t.toId;

            item->setData(
                t.id,
                t.dateTime,
                title,
                t.amount,
                t.fromBank,
                t.toBank,
                t.fromId,
                t.toId
                );

            ui->ScrollAreaOfHistory->layout()->addWidget(item);
        }
    } else {
        ui->NoHistoryText->show();
        ui->ScrollAreaOfHistory->hide();
    }


    // TransactionItem *item = new TransactionItem(this);
    // TransactionItem *item2 = new TransactionItem(this);

    // item->setData("โอน", 100, "1 พ.ค. 2569");
    // item2->setData("เติม", 100.53, "1 พ.ค. 2569");

    // ui->ScrollAreaOfHistory->layout()->addWidget(item);
    // ui->ScrollAreaOfHistory->layout()->addWidget(item2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshBalance()
{
    User& user = User::currentUser();

    double amount = user.getBalance();
    ui->BalanceLabel->setText(
        QString::number(amount, 'f', 2)
    );
}

void MainWindow::refreshHistory()
{
    Transaction transaction;
    QVector<TransactionRecord> list =
        transaction.getMyTransactions();

    QLayout *layout =
        ui->ScrollAreaOfHistory->layout();

    while (QLayoutItem* child = layout->takeAt(0)) {
        delete child->widget();
        delete child;
    }

    if (list.size() > 0) {
        ui->NoHistoryText->hide();
        ui->ScrollAreaOfHistory->show();
        for (const auto& t : std::as_const(list)) {
            TransactionItem *item = new TransactionItem(this);

            QString title;

            if (t.type == "transfer") {
                if (t.fromId == User::currentUser().getUserId())
                    title = "โอน";
                else
                    title = "รับเงิน";
            } else if (t.type == "topup") {

                title = "เติม";

            } else if (t.type == "withdraw") {

                title = "ถอน";

            } else {

                title = t.type;
            }

            // QString formattedDT = Helper::formatThaiDateTime(t.dateTime);

            qDebug() << "t.toId: " << t.toId;

            item->setData(
                t.id,
                t.dateTime,
                title,
                t.amount,
                t.fromBank,
                t.toBank,
                t.fromId,
                t.toId
                );

            ui->ScrollAreaOfHistory->layout()->addWidget(item);
        }
    } else {
        ui->NoHistoryText->show();
        ui->ScrollAreaOfHistory->hide();
    }
}

void MainWindow::on_TopupBtn_clicked()
{
    TopUpDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        refreshBalance();
        refreshHistory();
    }
}


void MainWindow::on_TransferBtn_clicked()
{
    TransferDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        refreshBalance();
        refreshHistory();
    }
}


void MainWindow::on_WithdrawBtn_clicked()
{
    ConfirmTransactionDialog dlg(
        TransactionType::Withdraw,
        "Mhee Bank",
        "",
        "",
        10
        );

    if (dlg.exec() == QDialog::Accepted) {
        refreshBalance();
        refreshHistory();
    }
}


void MainWindow::on_LogoutBtn_clicked()
{
    User::logout();
    emit logoutRequested();
    this->close();
    // LoginDialog login;
    // login.exec();
}

