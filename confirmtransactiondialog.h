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
        Transfer
    };
    explicit ConfirmTransactionDialog(TransactionType type, QWidget *parent = nullptr);
    ~ConfirmTransactionDialog();

private:
    TransactionType m_type;
    void setupUIByType();
    Ui::ConfirmTransactionDialog *ui;
};

#endif // CONFIRMTRANSACTIONDIALOG_H
