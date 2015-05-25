#include "passphraseform.h"
#include "ui_passphraseform.h"

Passphraseform::Passphraseform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Passphraseform)
{
    ui->setupUi(this);
}

Passphraseform::~Passphraseform()
{
    delete ui;
}
