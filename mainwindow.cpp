#include "backend/user.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include "transactionitem.h"
#include "topupdialog.h"
#include "transferdialog.h"
#include "backend/transaction.h"
#include "confirmtransactiondialog.h"

using TransactionType = ConfirmTransactionDialog::TransactionType;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    for (const auto& t : std::as_const(list)) {
        TransactionItem *item = new TransactionItem(this);

        QString title;

        if (t.type == "transfer") {
            if (t.fromId == User::currentUser().getUserId())
                title = "โอน";
            else
                title = "ถอน";
        } else if (t.type == "topup") {

            title = "เติม";

        } else {

            title = t.type;
        }

        item->setData(
            title,
            t.amount,
            t.dateTime
            );

        ui->ScrollAreaOfHistory->layout()->addWidget(item);
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

    for (const auto& t : std::as_const(list)) {

        TransactionItem *item =
            new TransactionItem(this);

        QString typeText;

        if (t.type == "transfer") {

            if (t.fromId == User::currentUser().getUserId())
                typeText = "โอน";
            else
                typeText = "ถอน";

        } else if (t.type == "topup") {

            typeText = "เติม";

        } else {

            typeText = t.type;
        }

        item->setData(typeText,
                      t.amount,
                      t.dateTime);

        layout->addWidget(item);
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
        0
        );

    dlg.exec();
}

