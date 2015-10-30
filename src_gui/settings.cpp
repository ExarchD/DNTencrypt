#include "settings.h"
#include "ui_settings.h"
#include <objects.h>
#include <iostream>
#include <string>
#include <qdebug.h>
#ifdef __WIN32__
#define __WIN32__WINNT
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#else
#include <arpa/inet.h>
#endif
settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    if (debug > 0 ) std::cout << "loading secret keys" << std::endl;
    std::vector<friends> list = list_friends(1);
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
    QString oldip = QString::fromStdString(server_ip);
    QString oldport = QString::fromStdString(port_value);
    ui->ip_lineEdit->setText(oldip);
    ui->port_lineEdit->setText(oldport);
    ui->combo_debug->setCurrentIndex(debug);
    ui->label_ipwarn->hide();
    ui->label_portwarn->hide();
}

settings::~settings()
{
    delete ui;
}

void settings::on_buttonBox_clicked(QAbstractButton *button)
{
    if (button->text() == "Apply"){
        std::string ip = ui->ip_lineEdit->text().toStdString();
        char str[INET_ADDRSTRLEN];
        struct sockaddr_in sa;
#ifdef __WIN32__
        if ( false ) ui->label_ipwarn->show();
#else
        if (inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 1 ) ui->label_2->show();
#endif
        else {
            ui->label_2->hide();
            config_edit("server_ip", ip);
        }

        std::string newport = ui->port_lineEdit->text().toStdString();
        config_edit("port", newport); 

        std::string raw_info=ui->combo_debug->currentText().toStdString();
        config_edit("debug", raw_info); 

        QString raw_infoemail=ui->comboBox->currentText();
        QStringList email_addr = raw_infoemail.split('}').first().split('{');
        std::string email = email_addr.last().toStdString();
        config_edit("user_email", email); 


    }
}
