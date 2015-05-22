#include "passphrase.h"
#include "ui_passphrase.h"
#include "objects.h"
Passphrase::Passphrase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Passphrase)
{
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    std::vector<friends> list = list_friends(1);
    for (int h=0; h < list.size(); h++) {
    const char * name = list[h].name.c_str();
    ui->comboBox->addItem(name);
    }
}

Passphrase::~Passphrase()
{
    delete ui;
}

void Passphrase::on_lineEdit_returnPressed()
{

   //check password
}

void Passphrase::on_pushButton_2_clicked()
{
    //cancel form
}

void Passphrase::on_pushButton_clicked()
{
    //check password
}
