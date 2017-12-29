#include "shapedialog.h"
#include "ui_shapedialog.h"

ShapeDialog::ShapeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShapeDialog)
{
    ui->setupUi(this);
}

ShapeDialog::~ShapeDialog()
{
    delete ui;
}
