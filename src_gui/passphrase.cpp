#include "passphrase.h"
#include "ui_passphrase.h"
#include "objects.h"
#include <string>
#include <qdebug.h>
#include <iostream>

Passphrase::Passphrase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Passphrase)
{
    ui->setupUi(this);
    if (debug > 0 ) std::cout << "loading secret keys" << std::endl;
//    ui->lineEdit->setEchoMode(QLineEdit::Password);
    std::vector<friends> list = list_friends(1);
    if (debug > 1 ) std::cout << "loaded secret keys" << std::endl;
    for (unsigned int h=0; h < list.size(); h++) {

    QString name = QString::fromStdString(list[h].name);
    QString email = QString::fromStdString(list[h].email);
            QString comb = name+" {"+email+"}";
    ui->comboBox->addItem(comb);
    if (email.toStdString() == user_email) {
        int index = ui->comboBox->findData(comb);
               ui->comboBox->setCurrentIndex(h);
    }
    }
    ui->pushButton_2->setAutoDefault(0);
}
Passphrase::~Passphrase()
{
    delete ui;
}

void Passphrase::on_pushButton_clicked()
{
   QString raw_info=ui->comboBox->currentText();
   QStringList email_addr = raw_info.split('}').first().split('{');
   std::string email = email_addr.last().toStdString();
   std::cout << email;
   config_edit("user_email", email); 
   load_key();
   this->close();
}

void Passphrase::on_pushButton_2_clicked()
{
   exit_program();
}
