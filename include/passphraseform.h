#ifndef PASSPHRASEFORM_H
#define PASSPHRASEFORM_H

#include <QWidget>

namespace Ui {
class Passphraseform;
}

class Passphraseform : public QWidget
{
    Q_OBJECT

public:
    explicit Passphraseform(QWidget *parent = 0);
    ~Passphraseform();

private:
    Ui::Passphraseform *ui;
};

#endif // PASSPHRASEFORM_H
