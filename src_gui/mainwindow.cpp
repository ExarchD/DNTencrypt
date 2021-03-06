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
#include <qrecorder.h>
#include <conversation.h>

std::vector<Conversation::gui_convo> known_chats;
QListWidgetItem *olditem;
int globcurrentconvo;

MainWindow::MainWindow(Conversation *myconvos, QMainWindow *parent) :


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
    num=5;
    load_config();
    load_key();
    mainconvos=myconvos;
    mainconvos->init();
    globcurrentconvo=-9;
    mainconvos->startretrieval_thread();
    regenerate_convolist(myconvos);
    ui->mytextEdit->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete mainconvos;
    delete ui;
}

void MainWindow::regenerate_convolist(Conversation *myconvos) {
    ui->listWidget_2->clear();
    new QListWidgetItem(tr("hidguy"), ui->listWidget_2);
    olditem=ui->listWidget_2->takeItem(0);
    olditem->setHidden(true);

    alltexts.clear();
    known_chats = myconvos->list();
    std::cout << "alltexts size " << alltexts.size() << std::endl;
    std::cout << "known convos size " << known_chats.size() << std::endl;
    for (unsigned int h=0; h < known_chats.size(); h++) {
        const char * name = known_chats[h].name.c_str();
        new QListWidgetItem(tr(name), ui->listWidget_2);

        QString docorig=ui->textBrowser->document()->toHtml();
        convocont newconvocont;
        newconvocont.doc=docorig;
        newconvocont.title=known_chats[h].name;
        alltexts.push_back(newconvocont);

    }
    std::cout << "alltexts size " << alltexts.size() << std::endl;

}
void MainWindow::anger() {
    regenerate_convolist(mainconvos);
}


void MainWindow::regenerate_friendlist(QString title) {
    ui->listWidget->clear();
    int currentconvo;
    for ( int citr =0; citr < known_chats.size(); citr++)
    {
        if (title.toStdString()==known_chats[citr].name) currentconvo=citr;
    }

    std::cout << known_chats[currentconvo].recipients.size() << std::endl;
    std::vector<std::string> conrec=known_chats[currentconvo].recipients;
    std::vector<friends> list = list_friends(0);
    std::vector<friends> shortlist;
    for (unsigned int h=0; h < list.size(); h++) {
        for (unsigned int k=0; k < conrec.size(); k++)
        {
            std::cout << conrec[k] << " " << list[h].email << std::endl;
            if (conrec[k] == list[h].email) {
                std::cout << "Matched" << std::endl;
                shortlist.push_back(list[h]);
            }
        }
    }

    for (unsigned int j=0; j < shortlist.size(); j++) {
        const char * name = shortlist[j].name.c_str();
        new QListWidgetItem(tr(name), ui->listWidget);
    }
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    for (unsigned int i = 0; i <  shortlist.size(); i++)
    {
        const char * email = shortlist[i].email.c_str();
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
    if (globcurrentconvo < 0 ) 
    {
        std::cout << "WARNING, no convo selected" << std::endl; 
        return;
    }

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
    /* main_encrypter(email_list, text); */
    mainconvos->send(email_list, text);
    ui->mytextEdit->setFocus();
}

void MainWindow::on_pushButton_clicked()
{
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
    ui->listWidget->update();


}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type()==QEvent::KeyPress) 
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) && !((key->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier)) 
        {
            sendMessage();
        } else {
            return QObject::eventFilter(obj, event);
        }
        return true;
    } 
    else
    {
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
}


void MainWindow::on_chatstart_pressed()
{


    chat = new chatinit(mainconvos);
    chat->show();
    connect(chat, SIGNAL(regen()), this, SLOT(anger()));
    chat->raise();
    chat->activateWindow();

}

void MainWindow::on_chatstart_clicked()
{

}

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
/* void MainWindow::on_listWidget_2_itemPressed(QListWidgetItem *item) */
{
  /* QTextDocument *docorig = new QTextDocument; */
    if (olditem->text().toStdString()!="hidguy")
    {
        std::cout <<"selected item" << std::endl;
        std::cout <<"number of convos " << alltexts.size() << std::endl;
        bool match=0;
        for ( int td=0; td < alltexts.size(); td++) 
        {
            if (alltexts[td].title == olditem->text().toStdString())
            {
                QString docorig=ui->textBrowser->document()->toHtml();
                alltexts[td].doc=docorig;
                match=1;
            }
        }
        if (!match)
        {
            QString docorig=ui->textBrowser->document()->toHtml();
            convocont newconvocont;
            newconvocont.doc=docorig;
            newconvocont.title=item->text().toStdString();
            alltexts.push_back(newconvocont);
        }
    }
    for ( int te=0; te < alltexts.size(); te++) 
    {
        if (alltexts[te].title == item->text().toStdString())
        {
            std::cout << "match" << std::endl;
            globcurrentconvo=te;
            ui->textBrowser->clear();
            QString newtext=alltexts[te].doc;
            ui->textBrowser->append(newtext);
            std::cout << "success" << std::endl;

        }
    }
    regenerate_friendlist(item->text());
    olditem=item;

}

