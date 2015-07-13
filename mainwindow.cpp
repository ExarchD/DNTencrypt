#include "mainwindow.h"
#include <ctime>
#include <fstream>
#include "ui_mainwindow.h"
#include "objects.h"
#include <qtconcurrentrun.h>
#include <passphrase.h>
#include <QKeyEvent>
#include <iostream>
#include <settings.h>

using namespace QtConcurrent;

MainWindow::MainWindow(QWidget *parent) :



    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if (debug > 0 ) std::cout << "window initialized" << std::endl;
    Passphrase *w = new Passphrase;
    this->hide();
    if (debug > 1 ) std::cout << "hiding window, loading passphrase dialog" << std::endl;
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




//std::string ip = ui->lineEdit->text().toStdString();
//char str[INET_ADDRSTRLEN];
//struct sockaddr_in sa;
// //test = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
// if (inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 1 ) ui->label_4->show();
// else {
//set_serverip(ip);

QString timestamp()
{
   time_t now = time(0);
   tm *ltm = localtime(&now);
//   if ((ltm->tm_min) < 10) std::cout << "HI" << std::endl;
   QString t_stamp=QString::number(ltm->tm_hour)+":"+QString::number(ltm->tm_min);
    return t_stamp;
}

void MainWindow::sendMessage(){
	std::string text = ui->mytextEdit->toPlainText().toStdString();
        ui->textBrowser->setTextColor(Qt::red);
	ui->textBrowser->append("Me ("+timestamp()+"): ");
        ui->textBrowser->setTextColor(Qt::black);
        ui->textBrowser->insertPlainText(ui->mytextEdit->toPlainText());
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


void MainWindow::on_quit_config_triggered()
{
    this->hide();
    exit_program();
}


void MainWindow::on_actionSettings_triggered()
{
             settings *sset= new settings();
    sset->show();
    sset->raise();
    sset->activateWindow();
}

void MainWindow::closeEvent (QCloseEvent *event)
{
 
    exit_program();
//    QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME,
//                                                                tr("Are you sure?\n"),
//                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
//                                                                QMessageBox::Yes);
//    if (resBtn != QMessageBox::Yes) {
//        event->ignore();
//    } else {
//        event->accept();
//    }
}


