#ifndef PASSPHRASE_H
#define PASSPHRASE_H

#include <QDialog>

namespace Ui {
class Passphrase;
}

class Passphrase : public QDialog
{
    Q_OBJECT

public:
    explicit Passphrase(QWidget *parent = 0);
    ~Passphrase();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Passphrase *ui;
};

#endif // PASSPHRASE_H
