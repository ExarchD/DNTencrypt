#include <QSettings>
#include <string>
#include "objects.h"
#include <iostream>

using namespace std;

void qsetvalue (QString key)
{

    QSettings settings("DNT", "config");
    QString stuff = settings.value(key).toString();
    cout << stuff.toStdString() << endl;

}

void qrecord(std::string key_new, std::string value_new) 
{
    QSettings settings("DNT", "config");
    QString qkey = QString::fromStdString(key_new);
    QString qvalue = QString::fromStdString(value_new);
    settings.setValue(qkey, qvalue);
    qsetvalue(qkey);
}

void qconvo(std::string convolog, int itr) 
{
    QSettings settings("DNT", "config");
    QString qconvo = QString::fromStdString(convolog);
    settings.beginGroup(qconvo);
    settings.setValue("itr", itr);
    settings.endGroup();
}
