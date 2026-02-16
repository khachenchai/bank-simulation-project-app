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

    void setData(QString title, double amount, QString date);

private:
    Ui::TransactionItem *ui;
};

#endif // TRANSACTIONITEM_H
