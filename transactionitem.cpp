#include "transactionitem.h"
#include "ui_transactionitem.h"
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QFileDialog>
#include "helper.h"
#include "backend/user.h"

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
    QString selfTransferTemplatePath = ":/assets/assets/img/slip_template/TransferMheeToMheeTemplate.png";
    QString transferToOtherBanksTemplatePath = ":/assets/assets/img/slip_template/TransferMheeToOtherBanksTemplate.png";
    QString withdrawTemplatePath = ":/assets/assets/img/slip_template/WithdrawTemplate.png";

    QString thePath;

    if (m_title == "เติม") thePath = topupTemplatePath;
    else if (m_title == "โอน" || m_title == "รับเงิน") {
        if (m_toBank != "Mhee Bank") thePath = transferToOtherBanksTemplatePath;
        else thePath = selfTransferTemplatePath;
    } else if (m_title == "ถอน") thePath = withdrawTemplatePath;

    QPixmap pixmap(thePath);
    if (pixmap.isNull()) return;

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QFont fontKanit("Kanit", 24);
    painter.setFont(fontKanit);
    painter.setPen(QColor(0,0,0));

    QDateTime dt = QDateTime::fromString(m_date, "yyyy-MM-dd HH:mm:ss");
    // QString displayDate = dt.toString("dd MMM yyyy HH:mm");

    QLocale thaiLocale(QLocale::Thai, QLocale::Thailand);
    QString thaiDate = thaiLocale.toString(dt, "dd MMMM yyyy HH:mm");

    painter.drawText(87,120, "วันที่ " + thaiDate + " น.");


    if (m_title == "เติม") {
        painter.drawText(160,405, "From User " + m_fromBank);
        painter.drawText(160,435, "xxx-xxx-xx");

        painter.drawText(540,405, User::getFullnameByUserId(m_toId).isEmpty() ? "Unknown User" : User::getFullnameByUserId(m_toId));
        painter.drawText(540,435, m_toId.isEmpty() ? "xxx-xxx-xx" : m_toId);

        painter.drawText(144,775, QString::number(m_id));
    } else if (m_title == "โอน" || m_title == "รับเงิน") {
        painter.drawText(160,405, User::getFullnameByUserId(m_fromId).isEmpty() ? "Unknown User" : User::getFullnameByUserId(m_fromId));
        painter.drawText(160,435, m_fromId.isEmpty() ? "xxx-xxx-xx" : m_fromId);

        painter.drawText(540,405, User::getFullnameByUserId(m_toId).isEmpty() ? "Unknown User" : User::getFullnameByUserId(m_toId));
        painter.drawText(540,435, m_toId.isEmpty() ? "xxx-xxx-xx" : m_toId);

        painter.drawText(144,775, QString::number(m_id));
    } else if (m_title == "ถอน") {
        painter.drawText(380,400, User::getFullnameByUserId(m_fromId).isEmpty() ? "Unknown User" : User::getFullnameByUserId(m_fromId));
        painter.drawText(450,445, m_fromId.isEmpty() ? "xxx-xxx-xx" : m_fromId);

        painter.drawText(144,775, QString::number(m_id));
    }

    // QLocale thai(QLocale::Thai);
    // QString formatted_amount = thai.toCurrencyString(m_amount, "");

    painter.drawText(144,875, QString::number(m_amount, 'f', 2) + " บาท");

    painter.drawText(144,975, "0 บาท");

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

