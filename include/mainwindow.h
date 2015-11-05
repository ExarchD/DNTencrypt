#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <conversation.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT  
    public:
        explicit MainWindow(Conversation *myconvos, QWidget *parent = 0);
        ~MainWindow();

        void regenerate_friendlist();
        void regenerate_convolist(Conversation *myconvos);
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

    private:
        Conversation myconvos;
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
