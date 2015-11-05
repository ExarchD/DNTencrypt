#include "chatinit.h"
#include "ui_chatinit.h"
#include "objects.h"
#include "conversation.h"
#include "iostream"

Conversation *chatconvo;

chatinit::chatinit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatinit)
{
    ui->setupUi(this);
    regenerate_list();
    ui->warn_notitle->hide();
}

chatinit::~chatinit()
{
    delete chatconvo;
    delete ui;
}


void chatinit::regenerate_list() {
    ui->friendlist->clear();
    std::vector<friends> list = list_friends(0);
    for (unsigned int h=0; h < list.size(); h++) {
        const char * name = list[h].name.c_str();
        new QListWidgetItem(tr(name), ui->friendlist);
    }
    ui->friendlist->setSelectionMode(QAbstractItemView::ExtendedSelection);
    for (unsigned int i = 0; i <  list.size(); i++)
    {
        const char * email = list[i].email.c_str();
        ui->friendlist->item(i)->setToolTip(email);
    }
}


void chatinit::on_includeb_pressed()
{

    QList<QListWidgetItem*> members = ui->friendlist->selectedItems();
    for (int i=0; i < members.count(); ++i) {
        QListWidgetItem* item = members[i];
        int row = ui->friendlist->row(item);
        QListWidgetItem *newitem = ui->friendlist->takeItem(row);
        ui->chatlist->addItem(newitem);
    }

}

void chatinit::on_excludeb_pressed()
{
    QList<QListWidgetItem*> members = ui->chatlist->selectedItems();
    for (int i=0; i < members.count(); ++i) {
        QListWidgetItem* item = members[i];
        int row = ui->chatlist->row(item);
        QListWidgetItem *newitem = ui->chatlist->takeItem(row);
        ui->friendlist->addItem(newitem);
    }

}

void chatinit::on_beginb_clicked()
{

    std::vector<std::string> email_list;
    email_list.clear();
    QList<QListWidgetItem*> recipients = ui->chatlist->selectedItems();
    for (int i=0; i < recipients.count(); ++i) {
        QListWidgetItem* item = recipients[i];
        email_list.push_back( item->toolTip().toStdString());
    }
    std::sort(email_list.begin(), email_list.end());

    QString salt = ui->chatsalt->text();
    QString title = ui->chattitle->text();
    
    if (salt.isEmpty() )
    {
        /* TODO: generate a random salt */
        salt="a38e48f821";
    }
    if (title.isEmpty() )
    {
        ui->warn_notitle->show();
    }
    else
    {

    chatconvo->add(email_list, salt.toStdString(), title.toStdString());
    close();
    }
}
