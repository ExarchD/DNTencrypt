#ifndef CHATINIT_H
#define CHATINIT_H

#include <QDialog>
#include <conversation.h>


namespace Ui {
class chatinit;
}

class chatinit : public QDialog
{
    Q_OBJECT

public:
    explicit chatinit(Conversation *chatconvo, QWidget *parent = 0);
    ~chatinit();
     
private slots:
    void on_includeb_pressed();

    void on_excludeb_pressed();

    void on_beginb_clicked();

signals:
    void regen();


private:
    Ui::chatinit *ui;
    Conversation *chatconvo;
    void regenerate_list();
};

#endif // CHATINIT_H
