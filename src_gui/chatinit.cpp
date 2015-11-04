#include "chatinit.h"
#include "ui_chatinit.h"

chatinit::chatinit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatinit)
{
    ui->setupUi(this);
}

chatinit::~chatinit()
{
    delete ui;
}

void chatinit::on_includeb_pressed()
{

}

void chatinit::on_excludeb_pressed()
{

}

void chatinit::on_beginb_pressed()
{

}
