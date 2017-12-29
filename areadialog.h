#ifndef AREADIALOG_H
#define AREADIALOG_H

#include <QDialog>

namespace Ui {
class AreaDialog;
}

class AreaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AreaDialog(QWidget *parent = 0);
    ~AreaDialog();

private:
    Ui::AreaDialog *ui;
};

#endif // AREADIALOG_H
