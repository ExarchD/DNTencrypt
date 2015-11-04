#ifndef CHATINIT_H
#define CHATINIT_H

#include <QDialog>

namespace Ui {
class chatinit;
}

class chatinit : public QDialog
{
    Q_OBJECT

public:
    explicit chatinit(QWidget *parent = 0);
    ~chatinit();

private slots:
    void on_includeb_pressed();

    void on_excludeb_pressed();

    void on_beginb_pressed();

private:
    Ui::chatinit *ui;
    void regenerate_list();
};

#endif // CHATINIT_H
