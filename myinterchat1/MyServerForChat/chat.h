#ifndef CHAT_H
#define CHAT_H
#include <QObject>
#include<QStringList>
#include<QJsonObject>
#include<QMap>
#include<QDebug>
#include<QJsonDocument>
#include<QStringList>
#include<QtNetwork/QNetworkInterface>
#include<QtNetwork/QNetworkAddressEntry>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<codedef.h>
#include<QVBoxLayout>
typedef struct
{
    QString name;
    QString ip;
}User;
class Chat:public QObject
{
     Q_OBJECT
public:
     explicit Chat(QObject *parent = 0);
    QString name;
    QStringList ips;
    QMap<QString,User*>others;

    int udp_fd;
    pthread_t tid;

    void init();
    void send(const QJsonObject&obj,QString ip);
    //void *recv_thread(void *ptr);
    void run();
    void handleMsg(const QJsonObject &obj,QString ip);
    void addUser(QString ip,QString name);

    QStringList getSysIps();
    QString getSysName();
   // static void *recv_thread(void *)
signals:
    void sigNewContent(QString,QString,bool);
    void sigNewUser(QString name,QString ip);
    void showip(QString,QString);

};

#endif // CHAT_H
