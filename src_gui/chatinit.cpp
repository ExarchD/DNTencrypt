#include "chatinit.h"
#include "ui_chatinit.h"
#include "objects.h"

chatinit::chatinit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatinit)
{
    ui->setupUi(this);
    regenerate_list();
}

chatinit::~chatinit()
{
    delete ui;
}


void chatinit::regenerate_list() {
    ui->friendlist->clear();
    std::vector<friends> list = list_friends(0);
    for (unsigned int h=0; h < list.size(); h++) {
        const char * name = list[h].name.c_str();
        new QListWidgetItem(tr(name), ui->friendlist);
    }
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    for (unsigned int i = 0; i <  list.size(); i++)
    {
        const char * email = list[i].email.c_str();
        ui->listWidget->item(i)->setToolTip(email);
    }
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
