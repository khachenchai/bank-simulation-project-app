#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include "transactionitem.h"
#include "topupdialog.h"

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

    TransactionItem *item = new TransactionItem(this);
    TransactionItem *item2 = new TransactionItem(this);

    item->setData("โอน", 100, "1 พ.ค. 2569");
    item2->setData("เติม", 100.53, "1 พ.ค. 2569");

    ui->ScrollAreaOfHistory->layout()->addWidget(item);
    ui->ScrollAreaOfHistory->layout()->addWidget(item2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TopupBtn_clicked()
{
    TopUpDialog dlg(this);
    dlg.exec();
}

