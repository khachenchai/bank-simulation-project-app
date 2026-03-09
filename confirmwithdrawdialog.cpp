#include "confirmwithdrawdialog.h"
#include "ui_confirmwithdrawdialog.h"
#include <QGraphicsDropShadowEffect>
#include "simulatedatmdialog.h"
#include <QDebug>

ConfirmWithdrawDialog::ConfirmWithdrawDialog(QString otpStr, double balance, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmWithdrawDialog),
    m_otpStr(otpStr),
    m_balance(balance)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(15);
    shadow->setOffset(0, 3);
    shadow->setColor(QColor(0, 0, 0, 40));
    ui->OTPLabel->setGraphicsEffect(shadow);

    ui->OTPLabel->setText(m_otpStr);

}

ConfirmWithdrawDialog::~ConfirmWithdrawDialog()
{
    delete ui;
}

void ConfirmWithdrawDialog::on_OpenATMBtn_clicked()
{
    qDebug() << m_balance;
    SimulatedATMDialog dlg(m_otpStr, m_balance, this);
    if (dlg.exec() == QDialog::Accepted) {
        accept();
    }
}

