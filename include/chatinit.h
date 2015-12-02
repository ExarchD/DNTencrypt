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
    /** 
     * @brief Adds an id to the new chat
     */
    void on_includeb_pressed();

    /** 
     * @brief Removes an id from the new chat
     */
    void on_excludeb_pressed();

    /** 
     * @brief Initializes the new chat
     */
    void on_beginb_clicked();

signals:
    /** 
     * @brief Signals the mainwindow to regenerate the chat list
     */
    void regen();


private:
    Ui::chatinit *ui;
    Conversation *chatconvo;
    /** 
     * @brief Loads up the friendslist by calling the Conversation object
     */
    void regenerate_list();
};

#endif // CHATINIT_H
