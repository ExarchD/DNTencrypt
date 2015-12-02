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
        /** 
         * @brief Generates the list of friends in a particular conversation
         * 
         * @param title The active conversation
         */
        void regenerate_friendlist(QString title);
        /** 
         * @brief Gets the list of conversations from the Conversation object MainWindow::mainconvos
         * 
         * @param myconvos
         */
        void regenerate_convolist(Conversation *myconvos);
        /** 
         * @brief This is the new chat dialog
         */
        chatinit *chat;
        /* std::vector<QTextDocument> all_texts; */

        public slots:
            /** 
             * @brief Slot to inform mainwindow that the chatinit::chatinit created a new 
             * chat. Named anger because it took me forever to figure out how
             * to use slots appropriately
             */
            void anger();

        private slots:
            /** 
             * @brief The big send button, this just triggers MainWindow::sendMessage
             */
            void on_pushButton_clicked();

            /** 
             * @brief Checks that there are recipients, then gathers that list and the
             * message and passes it to the conversation object MainWindow::mainconvos
             */
        void sendMessage();


        /** 
         * @brief Removes a user from the recipients list. Not useful in its current form anymore
         */
        void on_pushButton_3_clicked();

        /** 
         * @brief Allows the program to interpret return presses and trigger MainWindow::sendMessage
         * 
         * @param obj
         * @param event
         * 
         * @return 
         */
        bool eventFilter(QObject *obj, QEvent *event);

        /** 
         * @brief Closes window and initializes the exit_program()
         */
        void on_quit_config_triggered();

        /** 
         * @brief Opens the settings::settings window
         */
        void on_actionSettings_triggered();

        /** 
         * @brief Triggers from other close methods. We want to clean up properly
         * Otherwise we might loose convo information
         * 
         * @param event
         */
        void closeEvent (QCloseEvent *event);

        /** 
         * @brief Opens up chatinit::chatinit window
         */
        void on_chatstart_pressed();

        /** 
         * @brief Not used
         */
        void on_chatstart_clicked();

        /** 
         * @brief Loads up a conversation depending on which is clicked, and 
         * then generates list of recipients using MainWindow::regenerate_friendlist
         * 
         * @param item The clicked conversation item
         */
        void on_listWidget_2_itemClicked(QListWidgetItem *item);
        /* void on_listWidget_2_itemPressed(QListWidgetItem *item); */
         
private:
        Conversation *mainconvos;
        Ui::MainWindow *ui;
        /** 
         * @brief Session conversation message history
         */
        struct convocont
        {
            /** 
             * @brief Title of conversation
             */
        std::string title;
        /** 
         * @brief The actual conversation messages
         */
        QString doc;
        };
        /** 
         * @brief A vector of all loaded conversations and messges
         */
        std::vector<convocont> alltexts;
        /** 
         * @brief The old conversation that needs to be saved when
         * we switch with MainWindow::on_listWidget_2_itemClicked
         */
        QListWidgetItem *old_item;
};

#endif // MAINWINDOW_H
