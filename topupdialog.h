#ifndef TOPUPDIALOG_H
#define TOPUPDIALOG_H

#include <QDialog>

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
    void on_ConfirmBtn_clicked();

    void on_Top100_clicked();

    void on_Top300_clicked();

    void on_Top500_clicked();

    void on_Top1000_clicked();

    void on_Top2000_clicked();
    void resetTopUpButtons();

private:
    Ui::TopUpDialog *ui;
};

#endif // TOPUPDIALOG_H
