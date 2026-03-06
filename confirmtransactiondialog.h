#ifndef CONFIRMTRANSACTIONDIALOG_H
#define CONFIRMTRANSACTIONDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmTransactionDialog;
}

class ConfirmTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    enum class TransactionType {
        TopUp,
        Transfer,
        Withdraw
    };
    explicit ConfirmTransactionDialog(TransactionType type, QString fromBank, QString toBank, QString targetUserId, double balance, QWidget *parent = nullptr);
    ~ConfirmTransactionDialog();

private slots:
    void on_ConfirmBtn_clicked();

private:
    TransactionType m_type;
    QString m_fromBank;
    double m_balance;
    QString m_targetUserId;
    QString m_toBank;
    void setupUIByType();
    Ui::ConfirmTransactionDialog *ui;
};

#endif // CONFIRMTRANSACTIONDIALOG_H
