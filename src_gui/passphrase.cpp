#include "passphrase.h"
#include "ui_passphrase.h"
#include "objects.h"
#include <string>
#include <qdebug.h>
#include <iostream>
#ifdef __WIN32__
#define __WIN32__WINNT
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#else
#include <arpa/inet.h>
#endif

Passphrase::Passphrase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Passphrase)
{
    ui->setupUi(this);
    if (debug > 0 ) std::cout << "loading secret keys" << std::endl;
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
    /* Parsing key info */
    QString raw_info=ui->comboBox->currentText();
    QStringList email_addr = raw_info.split('}').first().split('{');
    std::string email = email_addr.last().toStdString();
    std::cout << email;
    /* parsing ip info */
    std::string ip = ui->lineEdit->text().toStdString();

    /* parsing port info */
    std::string newport = ui->lineEdit_2->text().toStdString();

    /* saving info to config file */
    char str[INET_ADDRSTRLEN];
    struct sockaddr_in sa;
#ifdef __WIN32__
    if ( false ) ui->label_2->show();
#else
    if (inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 1 ) ui->label_2->show();
#endif
    else {
        ui->label_2->hide();
        config_edit("server_ip", ip);
    }
    config_edit("user_email", email); 
    config_edit("port", newport); 

    /* loading appropriate key */
    load_key();


    this->close();
}

void Passphrase::on_pushButton_2_clicked()
{
    exit_program();
}
