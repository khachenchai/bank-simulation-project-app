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
    explicit ConfirmWithdrawDialog(QWidget *parent = nullptr);
    ~ConfirmWithdrawDialog();

private:
    Ui::ConfirmWithdrawDialog *ui;
};

#endif // CONFIRMWITHDRAWDIALOG_H
