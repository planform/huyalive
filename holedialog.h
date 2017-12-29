#ifndef HOLEDIALOG_H
#define HOLEDIALOG_H

#include <QDialog>

namespace Ui {
class HoleDialog;
}

class HoleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HoleDialog(QWidget *parent = 0);
    ~HoleDialog();

private:
    Ui::HoleDialog *ui;
};

#endif // HOLEDIALOG_H
