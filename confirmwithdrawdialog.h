#ifndef CONFIRMWITHDRAWDIALOG_H
#define CONFIRMWITHDRAWDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmWithdrawDialog;
}

class ConfirmWithdrawDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmWithdrawDialog(QString otpStr, double balance, QWidget *parent = nullptr);
    ~ConfirmWithdrawDialog();

private slots:
    void on_OpenATMBtn_clicked();

private:
    Ui::ConfirmWithdrawDialog *ui;
    QString m_otpStr;
    double m_balance;
};

#endif // CONFIRMWITHDRAWDIALOG_H
