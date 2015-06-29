#include "passphrase.h"
#include "ui_passphrase.h"
#include "objects.h"
#include <string>
#include <qdebug.h>
#include <arpa/inet.h>

Passphrase::Passphrase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Passphrase)
{
    ui->setupUi(this);
    ui->label_4->hide();
//    ui->lineEdit->setEchoMode(QLineEdit::Password);
    std::vector<friends> list = list_friends(1);
    for (unsigned int h=0; h < list.size(); h++) {
//    const char * name = list[h].name.c_str();
//    const char * email = list[h].email.c_str();
    QString name = QString::fromStdString(list[h].name);
    QString email = QString::fromStdString(list[h].email);
            QString comb = name+" {"+email+"}";
    ui->comboBox->addItem(comb);
    }
    ui->lineEdit->setFocus();
   // ui->pushButton->setAutoDefault(0);
    ui->pushButton_2->setAutoDefault(0);
}
Passphrase::~Passphrase()
{
    delete ui;
}

void Passphrase::on_lineEdit_returnPressed()
{
   std::string pass= ui->lineEdit->text().toStdString();
   QString raw_info=ui->comboBox->currentText();
   QStringList email_addr = raw_info.split('}').first().split('{');
   std::string email = email_addr.last().toStdString();
//    qDebug() << email_addr.first() << email_addr.last();
//   int success = unlock_master_key(pass,email);
//   if (!success) on_label_linkActivated("failed");
   //check password
}

void Passphrase::on_label_linkActivated(const QString &link)
{
  ui->label->setText("Wrong passphrase, please try again");
}

void Passphrase::on_pushButton_clicked()
{
   QString raw_info=ui->comboBox->currentText();
   QStringList email_addr = raw_info.split('}').first().split('{');
   std::string email = email_addr.last().toStdString();
   std::string ip = ui->lineEdit->text().toStdString();
   char str[INET_ADDRSTRLEN];
   struct sockaddr_in sa;
    //test = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
    if (inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 1 ) ui->label_4->show();
    else {
   set_serverip(ip);
   set_user(email);
   this->close();
}
}

void Passphrase::on_pushButton_2_clicked()
{
   exit_program();
}
