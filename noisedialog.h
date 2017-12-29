#ifndef NOISEDIALOG_H
#define NOISEDIALOG_H

#include <QDialog>

namespace Ui {
class NoiseDialog;
}

class NoiseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoiseDialog(QWidget *parent = 0);
    ~NoiseDialog();

private:
    Ui::NoiseDialog *ui;
};

#endif // NOISEDIALOG_H
