#include "transactionitem.h"
#include "ui_transactionitem.h"
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QFileDialog>
#include "helper.h"

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

void TransactionItem::setData(int id, QString date, QString transaction,
                              double amount, QString from_bank,
                              QString to_bank, QString fromId, QString toId)
{
    QString title = transaction;

    m_id = id;
    m_title = title;
    m_amount = amount;
    m_date = date;
    m_fromBank = from_bank;
    m_toBank = to_bank;
    m_fromId = fromId;
    m_toId = toId;

    ui->labelTitle->setText(title);
    QString formattedAmount = "";
    if (title == "โอน" || title == "ถอน") formattedAmount += "- ";
    else if (title == "เติม" || title == "รับเงิน") formattedAmount += "+ ";
    formattedAmount += QString::number(amount);
    ui->labelAmount->setText(formattedAmount + " บาท");
    QString formattedDT = Helper::formatThaiDateTime(date);
    ui->labelDate->setText(formattedDT);

    if (title == "โอน" || title == "ถอน")
        ui->labelAmount->setStyleSheet(
            "font-size:16px;"
            "color:red;"
            );
    else if (title == "เติม" || title == "รับเงิน")
        ui->labelAmount->setStyleSheet(
            "font-size:16px;"
            "font-weight:bold;"
            "color:green;"
            );
}


void TransactionItem::on_loadSlipBtn_clicked()
{
    QString topupTemplatePath = ":/assets/assets/img/slip_template/TopupTemplate.png";
    QPixmap pixmap(topupTemplatePath);
    if (pixmap.isNull()) return;

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QFont fontKanit("Kanit", 24);
    painter.setFont(fontKanit);
    painter.setPen(QColor(0,0,0));

    QDateTime dt = QDateTime::fromString(m_date, "yyyy-MM-dd HH:mm:ss");
    QString displayDate = dt.toString("dd MMM yyyy HH:mm");

    painter.drawText(87,120, "วันที่ " + displayDate + " น.");


    painter.drawText(200,405, "From User Bank A");
    painter.drawText(200,435, "xxx-xxx-xx");

    painter.drawText(144,775, QString::number(m_id));

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save Slip",
        "slip.png",
        "PNG Files (*.png)"
        );

    if (!fileName.isEmpty())
    {
        pixmap.save(fileName);
    }
}

