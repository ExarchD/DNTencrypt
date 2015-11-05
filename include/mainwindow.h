#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT  
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void regenerate_friendlist();
        void regenerate_convolist();
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
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
