#include "mainwindow.h"
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


void MainWindow::sendMessage(){
	std::string text = ui->mytextEdit->toPlainText().toStdString();
	ui->textBrowser->append(ui->mytextEdit->toPlainText());
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


void MainWindow::keyPressEvent ( QKeyEvent * e ) {
   // das shift+return event wollen wir nicht, weil sonst ein <br> statt ein <p> gemacht wird
   // return => 16777220
   if ((e->key() == Qt::Key_Enter || e->key() == 16777220) && ((e->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier)) {
      // clone object but without shift
      // current modifiers & all possible modifiers, but SHIFT,ALT,CTRL
      e = new QKeyEvent(e->type(), e->key(), e->modifiers()&Qt::MetaModifier&Qt::KeypadModifier, e->text(), e->isAutoRepeat(), (ushort) e->count());
   }
//   QTextEdit::keyPressEvent(e);
}



bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
     if (obj == ui->mytextEdit) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *e = static_cast<QKeyEvent*>(event);
            if ((e->key() == Qt::Key_Enter || e->key() == 16777220) && !((e->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier)) {
                sendMessage();
            }
        }
     }
}
