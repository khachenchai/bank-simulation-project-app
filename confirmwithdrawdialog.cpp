#include "confirmwithdrawdialog.h"
#include "ui_confirmwithdrawdialog.h"
#include <QGraphicsDropShadowEffect>

ConfirmWithdrawDialog::ConfirmWithdrawDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmWithdrawDialog)
{
    ui->setupUi(this);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(15);
    shadow->setOffset(0, 3);
    shadow->setColor(QColor(0, 0, 0, 40));
    ui->OTPLabel->setGraphicsEffect(shadow);
}

ConfirmWithdrawDialog::~ConfirmWithdrawDialog()
{
    delete ui;
}
