#ifndef SIMULATEDATMDIALOG_H
#define SIMULATEDATMDIALOG_H

#include <QDialog>

namespace Ui {
class SimulatedATMDialog;
}

class SimulatedATMDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SimulatedATMDialog(QString otpStr, double balance, QWidget *parent = nullptr);
    ~SimulatedATMDialog();

private slots:
    void on_ConfirmBtn_clicked();

private:
    Ui::SimulatedATMDialog *ui;
    QString m_otpStr;
    double m_balance;
};

#endif // SIMULATEDATMDIALOG_H
