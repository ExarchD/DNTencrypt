#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    new QListWidgetItem(tr("Oak"), ui->listWidget);
    new QListWidgetItem(tr("Fir"), ui->listWidget);
    new QListWidgetItem(tr("Pine"), ui->listWidget);
    new QListWidgetItem(tr("Bircth"), ui->listWidget);
    new QListWidgetItem(tr("Hazel"), ui->listWidget);
    new QListWidgetItem(tr("Redwood"), ui->listWidget);
    new QListWidgetItem(tr("Sycamore"), ui->listWidget);
    new QListWidgetItem(tr("Chestnut"), ui->listWidget);
    new QListWidgetItem(tr("Mahogany"), ui->listWidget);
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

}

MainWindow::~MainWindow()
{
    delete ui;
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


