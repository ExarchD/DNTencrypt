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


void load_config () 
{
    QSettings settings("DNT", "config");
    foreach (const QString &key, settings.childKeys()) {
        qsetvalue (key);
    }

}

void record_convos(std::vector <enc_convo> allenc_convos)
{
    cout << "Now recording" << endl;
    QSettings settings("DNT", "config");
    for (int x=0; x < allenc_convos.size(); x++)
    {
        cout << "Recording " << x << "conversation" << endl;
        std::string name="convo"+std::to_string(x);
        QString qname=QString::fromStdString(name);
        settings.beginGroup(qname);
        settings.setValue(QString::fromStdString("enc_info"),QString::fromStdString(allenc_convos[x].enc_info));
        settings.setValue(QString::fromStdString("itr"),allenc_convos[x].iterator);
        settings.setValue(QString::fromStdString("urgency"),allenc_convos[x].urgency);
        settings.setValue(QString::fromStdString("resp"),allenc_convos[x].noresponse);
        settings.endGroup();
    }
}

std::vector <enc_convo> load_convos () 
{
    QSettings settings("DNT", "config");
    std::vector <enc_convo> allconvos;
    foreach (const QString &group, settings.childGroups()) 
    {
        settings.beginGroup(group);
        enc_convo indivconvo;
        foreach (const QString &key, settings.childKeys()) 
        {
            cout << key.toStdString() << endl;
            QString stuff = settings.value(key).toString();
            if (key=="enc_info") indivconvo.enc_info=stuff.toStdString();
            if (key=="itr") indivconvo.iterator=stuff.toInt();
            if (key=="urgency") indivconvo.urgency=stuff.toInt();
            if (key=="resp") indivconvo.noresponse=stuff.toInt();
        }
        allconvos.push_back(indivconvo);
    }
    return allconvos;
}
