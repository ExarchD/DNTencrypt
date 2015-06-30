#include "mainwindow.h"
#include <ctime>
#include <fstream>
#include "ui_mainwindow.h"
#include "objects.h"
#include <QThread>
#include <qtconcurrentrun.h>
#include <passphrase.h>
#include <QKeyEvent>
#include <iostream>

using namespace QtConcurrent;

MainWindow::MainWindow(QWidget *parent) :



    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Passphrase *w = new Passphrase;
    this->hide();
    int result = w->exec();
    this->show();
    delete w;
    ui->setupUi(this);
    ui->mytextEdit->installEventFilter(this);
    regenerate_list();
  
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::regenerate_list() {
    ui->listWidget->clear();
    std::vector<friends> list = list_friends(0);
    for (unsigned int h=0; h < list.size(); h++) {
    const char * name = list[h].name.c_str();
    new QListWidgetItem(tr(name), ui->listWidget);
    }
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    for (unsigned int i = 0; i <  list.size(); i++)
    {
       const char * email = list[i].email.c_str();
     ui->listWidget->item(i)->setToolTip(email);
            }
}


std::string timestamp()
{
   time_t now = time(0);
   tm *ltm = localtime(&now);
   std::string t_stamp=std::to_string(ltm->tm_hour)+":"+std::to_string(ltm->tm_min);
    return t_stamp;
}

void MainWindow::sendMessage(){
	std::string text = ui->mytextEdit->toPlainText().toStdString();
        
	ui->textBrowser->append("Me ("+QString::fromUtf8(timestamp().c_str())+"): "+ ui->mytextEdit->toPlainText());
        ui->mytextEdit->clear();
	std::vector<std::string> email_list;
	email_list.clear();
	QList<QListWidgetItem*> recipients = ui->listWidget->selectedItems();
	for (int i=0; i < recipients.count(); ++i) {
	 QListWidgetItem* item = recipients[i];
	 email_list.push_back( item->toolTip().toStdString());
	}
	std::sort(email_list.begin(), email_list.end());
	encrypter(email_list, text);
        ui->mytextEdit->setFocus();
}

void MainWindow::on_pushButton_clicked()
{
    QList<QListWidgetItem*> recipients = ui->listWidget->selectedItems();
    for (unsigned int i=0; i < recipients.count(); ++i) {
     QListWidgetItem* item = recipients[i];
    }
  sendMessage();


//  QFuture<void> f1 = run(retrieve);
}



void MainWindow::on_pushButton_3_clicked()
{
//    QList<QListWidgetItem*> recipients = ui->listWidget->selectedItems();
//    for (int i=0; i < recipients.count(); ++i) {
//     QListWidgetItem* item = recipients[i];



    std::ofstream outfile;
    outfile.open("rejected.txt", std::ios_base::app);
    QList<QListWidgetItem*> recipients = ui->listWidget->selectedItems();
    for (int i=0; i < recipients.count(); ++i) {
     QListWidgetItem* item = recipients[i];
     outfile << item->toolTip().toStdString();
     outfile << "\n";
    }
    outfile.close();
     regenerate_list();
     ui->listWidget->update();


}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
//        if ((e->key() == Qt::Key_Enter || e->key() == 16777220){
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) && !((key->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier)) {
            sendMessage();
        } else {
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}

