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

    void regenerate_list();
private slots:
    void on_pushButton_clicked();

    void sendMessage();

    void on_pushButton_3_clicked();

    bool eventFilter(QObject *obj, QEvent *event);

    void on_quit_config_triggered();

    void on_actionSettings_triggered();

    void closeEvent (QCloseEvent *event);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H