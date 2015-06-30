#include "settings.h"
#include <arpa/inet.h>
#include "ui_settings.h"
#include <objects.h>
#include <iostream>

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
     if (inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 1 ) ui->label_2->show();
     else {
         ui->label_2->hide();
    set_serverip(ip);
     }
    }
}
