#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QListWidget>
#include<QTextBrowser>
#include<QTextEdit>
#include<QPushButton>
#include"chat.h"
#include<QJsonDocument>
#include<QStringList>
#include<QtNetwork/QNetworkInterface>
#include<QtNetwork/QNetworkAddressEntry>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<codedef.h>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QSplitter>
#include<signal.h>
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    Chat chat;
    QListWidget *userList;
    QTextBrowser*msgShow;
    QTextEdit*msgInput;
    QPushButton *sendMsg;
    QPushButton *setup;
    QPushButton *sendFile;
    MyWidget(QWidget *parent = 0);
    ~MyWidget();
public slots:
    void onShowIp(QString,QString);
    void onSend();
    void showcontent(QString,QString,bool);

};

#endif // MYWIDGET_H
