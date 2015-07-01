#include "settings.h"
#include "ui_settings.h"
#include <objects.h>
#include <iostream>
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
    ui->label_2->hide();
}

settings::~settings()
{
    delete ui;
}

void settings::on_buttonBox_clicked(QAbstractButton *button)
{
    std::cout << button->text().toStdString() << std::endl;
    if (button->text() == "Apply"){
    std::string ip = ui->lineEdit->text().toStdString();
    char str[INET_ADDRSTRLEN];
    struct sockaddr_in sa;
    #ifdef __WIN32__
    if ( false ) ui->label_2->show();
#else
     if (inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 1 ) ui->label_2->show();
#endif
     else {
         ui->label_2->hide();
    set_serverip(ip);
     }
    }
}
