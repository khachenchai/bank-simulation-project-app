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
    explicit SimulatedATMDialog(QWidget *parent = nullptr);
    ~SimulatedATMDialog();

private:
    Ui::SimulatedATMDialog *ui;
};

#endif // SIMULATEDATMDIALOG_H
