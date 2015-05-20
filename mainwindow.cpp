#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "objects.h"



MainWindow::MainWindow(QWidget *parent) :



    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    regenerate_list();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::regenerate_list() {
    ui->listWidget->clear();
    std::vector<friends> list = list_friends();
    for (int h=0; h < list.size(); h++) {
    const char * name = list[h].name.c_str();
    new QListWidgetItem(tr(name), ui->listWidget);
    }
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    for (int i = 0; i <  list.size(); i++)
    {
       const char * email = list[i].email.c_str();
     ui->listWidget->item(i)->setToolTip(email);
            }
}


void MainWindow::sendMessage(){
        //QString text = ui->textEdit->toPlainText();
        //ui->textEdit->clear();
        //ui->textBrowser->append(text);
}

void MainWindow::on_pushButton_clicked()
{
    QList<QListWidgetItem*> recipients = ui->listWidget->selectedItems();
    for (int i=0; i < recipients.count(); ++i) {
     QListWidgetItem* item = recipients[i];
     ui->textBrowser->append(item->text());
    }
}



void MainWindow::on_pushButton_3_clicked()
{
//    QList<QListWidgetItem*> recipients = ui->listWidget->selectedItems();
//    for (int i=0; i < recipients.count(); ++i) {
//     QListWidgetItem* item = recipients[i];

 	
    QList<QListWidgetItem*> recipients = ui->listWidget->selectedItems();
    for (int i=0; i < recipients.count(); ++i) {
     QListWidgetItem* item = recipients[i];
     ui->textBrowser->append(item->toolTip());
    }
 regenerate_list();
}
