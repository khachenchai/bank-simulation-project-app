#ifndef TRANSFERDIALOG_H
#define TRANSFERDIALOG_H

#include <QDialog>

namespace Ui {
class TransferDialog;
}

class TransferDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransferDialog(QWidget *parent = nullptr);
    ~TransferDialog();

private slots:
    void on_SubmitBtn_clicked();

private:
    Ui::TransferDialog *ui;
};

#endif // TRANSFERDIALOG_H
