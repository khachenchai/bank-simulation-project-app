#include "simulatedatmdialog.h"
#include "ui_simulatedatmdialog.h"

SimulatedATMDialog::SimulatedATMDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SimulatedATMDialog)
{
    ui->setupUi(this);

}

SimulatedATMDialog::~SimulatedATMDialog()
{
    delete ui;
}
