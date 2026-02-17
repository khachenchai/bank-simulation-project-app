#include "topupdialog.h"
#include "ui_topupdialog.h"

TopUpDialog::TopUpDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TopUpDialog)
{
    ui->setupUi(this);
}

TopUpDialog::~TopUpDialog()
{
    delete ui;
}
