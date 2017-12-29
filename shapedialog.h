#ifndef SHAPEDIALOG_H
#define SHAPEDIALOG_H

#include <QDialog>

namespace Ui {
class ShapeDialog;
}

class ShapeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShapeDialog(QWidget *parent = 0);
    ~ShapeDialog();

private:
    Ui::ShapeDialog *ui;
};

#endif // SHAPEDIALOG_H
