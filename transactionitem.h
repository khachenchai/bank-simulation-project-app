#ifndef TRANSACTIONITEM_H
#define TRANSACTIONITEM_H

#include <QWidget>

namespace Ui {
class TransactionItem;
}

class TransactionItem : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionItem(QWidget *parent = nullptr);
    ~TransactionItem();

    void setData(int id, QString date, QString transaction,
                 double amount, QString from_bank,
                 QString to_bank, QString fromId, QString toId);

private slots:
    void on_loadSlipBtn_clicked();
    void on_descBtn_clicked();

private:
    Ui::TransactionItem *ui;
    QString m_title;
    QString m_date;
    double m_amount;
    int m_id;
    QString m_transactionType;
    QString m_fromBank;
    QString m_toBank;
    QString m_fromId;
    QString m_toId;
};

#endif // TRANSACTIONITEM_H
