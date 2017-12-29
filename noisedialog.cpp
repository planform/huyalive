#include "noisedialog.h"
#include "ui_noisedialog.h"

NoiseDialog::NoiseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoiseDialog)
{
    ui->setupUi(this);
}

NoiseDialog::~NoiseDialog()
{
    delete ui;
}
