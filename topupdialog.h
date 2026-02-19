#ifndef TOPUPDIALOG_H
#define TOPUPDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class TopUpDialog;
}

class TopUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TopUpDialog(QWidget *parent = nullptr);
    ~TopUpDialog();

private slots:
    void onBankAClicked();
    void onBankBClicked();
    void onSubmitClicked();

private:
    Ui::TopUpDialog *ui;
    QString selectedBank;
};

#endif // TOPUPDIALOG_H
