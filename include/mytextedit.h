#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H
#include <QPlainTextEdit>



class MyTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit MyTextEdit(QWidget *parent = 0);

//protected:
//    void keyPressEvent(QKeyEvent *e);


   ~MyTextEdit();

};

#endif // MYTEXTEDIT_H
