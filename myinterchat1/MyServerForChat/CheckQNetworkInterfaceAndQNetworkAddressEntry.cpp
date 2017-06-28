//#include "mywidget.h"
#include <QApplication>
#include<QNetworkInterface>
#include<QHostAddress>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MyWidget w;
   // w.show();
    QStringList ret;

    //QList<QNetworkInterface>infs=QNetworkInterface::allInterfaces();
     QList<QHostAddress>infs=QNetworkInterface::allAddresses();
    foreach(QHostAddress infss,infs)
    {
        qDebug()<<infss.toString();
    }

     //    foreach(QNetworkInterface infss,infs)
//    {
//        entrys.append(infss.addressEntries());
//    }

//    foreach(QNetworkAddressEntry entrys1,entrys)
//    {
//        qDebug()<<entrys1.ip().toString()<<"mmm";
//    }

//    QStringList Chat::getSysIps()
//    {
//        QStringList ret;
//        QList<QNetworkAddressEntry>entrys;

//        QList<QNetworkInterface>infs=QNetworkInterface::allInterfaces();
//        foreach(QNetworkInterface inf,infs)
//        {
//            entrys.append(inf.addressEntries());
//        }

//        foreach(QNetworkAddressEntry entry,entrys)
//        {
//            if(entry.ip().toString().length()!=0)
//                ret.append(entry.ip().toString());
//            ret.append(entry.ip().toString());
//        }

//        return ret;



    return a.exec();
}
