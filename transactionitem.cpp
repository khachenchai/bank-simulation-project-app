#include "transactionitem.h"
#include "ui_transactionitem.h"

TransactionItem::TransactionItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TransactionItem)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true);
}

TransactionItem::~TransactionItem()
{
    delete ui;
}

void TransactionItem::setData(QString title, double amount, QString date)
{
    ui->labelTitle->setText(title);
    QString formattedAmount = "";
    if (title == "โอน" || title == "ถอน") formattedAmount += "- ";
    else if (title == "เติม") formattedAmount += "+ ";
    formattedAmount += QString::number(amount);
    ui->labelAmount->setText(formattedAmount + " บาท");
    ui->labelDate->setText(date);

    if (title == "โอน" || title == "ถอน")
        ui->labelAmount->setStyleSheet(
            "font-size:16px;"
            "color:red;"
            );
    else if (title == "เติม")
        ui->labelAmount->setStyleSheet(
            "font-size:16px;"
            "font-weight:bold;"
            "color:green;"
            );
}
