#include "mainwindow.h"
#include <ctime>
#include <fstream>
#include "ui_mainwindow.h"
#include "objects.h"
#include <passphrase.h>
#include <chatinit.h>
#include <QKeyEvent>
#include <QSettings>
#include <iostream>
#include <settings.h>
#include <conversation.h>

std::vector<Conversation::gui_convo> known_chats;

MainWindow::MainWindow(Conversation *myconvos, QWidget *parent) :


    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if (debug > 0 ) std::cout << "window initialized" << std::endl;
    QSettings settings("DNT", "config");
    if(!settings.contains("port") || !settings.contains("server_ip") || !settings.contains("user_email") )
    {
        Passphrase *w = new Passphrase;
        this->hide();
        if (debug > 1 ) std::cout << "hiding window, loading passphrase dialog" << std::endl;
        int result = w->exec();
        this->show();
        delete w;
        qrecord("debug","0");
    }
    ui->setupUi(this);
    load_config();
    load_key();
    mainconvos=myconvos;
    regenerate_convolist(myconvos);
    ui->mytextEdit->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    /* delete myconvo; */
    delete ui;
}

void MainWindow::regenerate_convolist(Conversation *myconvos) {
    ui->listWidget_2->clear();
    known_chats = myconvos->list();
    for (unsigned int h=0; h < known_chats.size(); h++) {
        const char * name = known_chats[h].name.c_str();
        new QListWidgetItem(tr(name), ui->listWidget_2);
    }
}

void MainWindow::regenerate_friendlist() {
    ui->listWidget->clear();
    std::cout <<  ui->listWidget_2->currentItem()->text().toStdString() << std::endl;
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


QString timestamp()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
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
    main_encrypter(email_list, text);
    ui->mytextEdit->setFocus();
    /* myconvo->send(email_list, text); */
}

void MainWindow::on_pushButton_clicked()
{
    /* QList<QListWidgetItem*> recipients = ui->listWidget->selectedItems(); */
    /* for (unsigned int i=0; i < recipients.count(); ++i) { */
    /*     QListWidgetItem* item = recipients[i]; */
    /* } */
    sendMessage();
}

void MainWindow::on_pushButton_3_clicked()
{

    std::ofstream outfile;
    outfile.open("rejected.txt", std::ios_base::app);
    QList<QListWidgetItem*> recipients = ui->listWidget->selectedItems();
    for (int i=0; i < recipients.count(); ++i) {
        QListWidgetItem* item = recipients[i];
        outfile << item->toolTip().toStdString();
        outfile << "\n";
    }
    outfile.close();
    /* regenerate_list(); */
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



    void MainWindow::on_chatstart_pressed()
    {

        
        chatinit *chat = new chatinit(mainconvos);
        /* chatinit chat(mainconvos,&parent); */
        /* chat->setParent(this); */
        /* chatinit chat(mainconvos); */
    /* MainWindow w(&convos); */
        chat->show();
        chat->raise();
        chat->activateWindow();
        regenerate_convolist(mainconvos);

    }

    void MainWindow::on_chatstart_clicked()
    {

    }

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{

regenerate_friendlist();
}
