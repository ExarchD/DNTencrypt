#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>
#include <conversation.h>
#include <QObject>
#include <chatinit.h>
#include <QTextDocument>
#include <vector>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT  
    public:
        explicit MainWindow(Conversation *myconvos, QMainWindow *parent = 0);
        ~MainWindow();

        int num;
        void regenerate_friendlist(QString title);
        void regenerate_convolist(Conversation *myconvos);
        chatinit *chat;
        /* std::vector<QTextDocument> all_texts; */

        public slots:
            void anger();

        private slots:
            void on_pushButton_clicked();

        void sendMessage();


        void on_pushButton_3_clicked();

        bool eventFilter(QObject *obj, QEvent *event);

        void on_quit_config_triggered();

        void on_actionSettings_triggered();

        void closeEvent (QCloseEvent *event);

        void on_chatstart_pressed();

        void on_chatstart_clicked();

        void on_listWidget_2_itemClicked(QListWidgetItem *item);
         
private:
        Conversation *mainconvos;
        Ui::MainWindow *ui;
        struct convocont
        {
        std::string title;
        QTextDocument* doc;
        };
        std::vector<convocont> alltexts;
        QListWidgetItem *old_item;
};

#endif // MAINWINDOW_H
