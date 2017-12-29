#include "holedialog.h"
#include "ui_holedialog.h"

HoleDialog::HoleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HoleDialog)
{
    ui->setupUi(this);
}

HoleDialog::~HoleDialog()
{
    delete ui;
}
