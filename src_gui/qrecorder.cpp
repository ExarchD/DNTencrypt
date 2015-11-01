#include <QSettings>
#include <string>
#include "objects.h"
#include <iostream>

using namespace std;

void qsetvalue (QString key)
{

    QSettings settings("DNT", "config");
    QString stuff = settings.value(key).toString();
    cout << key.toStdString() << endl;
    cout << stuff.toStdString() << endl;
    if (key == "port")
        port_value=stuff.toInt();
    if (key == "debug")
        debug=stuff.toInt();
    if (key == "server_ip")
        server_ip=stuff.toStdString();
    if (key == "user_email")
        user_email=stuff.toStdString();

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

void load_config () {

    QSettings settings("DNT", "config");
    foreach (const QString &key, settings.childKeys()) {
        qsetvalue (key);
    }

}

void save_convos( vector<convo> savelist)
{
    for (int x = 0; x < savelist.size(); x++ )
    {
        qconvo(savelist[x].hash, savelist[x].iterator);
    }
}

std::vector <convo> load_convos () {
    QSettings settings("DNT", "config");
    foreach (const QString &group, settings.childGroups()) {
    cout << group.toStdString() << endl;
    }

}
