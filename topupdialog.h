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

private:
    Ui::TopUpDialog *ui;
};

#endif // TOPUPDIALOG_H
