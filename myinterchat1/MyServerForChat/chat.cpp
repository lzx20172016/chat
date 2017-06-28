#include "chat.h"

#include<QThread>
Chat::Chat(QObject *parent):QObject(parent)
{

    ips=getSysIps();
    foreach(QString ipss,ips)
    {
        qDebug()<<ipss;
    }
    name=getSysName();
    qDebug()<<"name"<<name;

}


void Chat::send(const QJsonObject&obj,QString ip)
{
    QByteArray buf=QJsonDocument(obj).toJson();
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(9988);
    addr.sin_addr.s_addr=inet_addr(ip.toUtf8().data());
    QString name=obj.value("name").toString();
    qDebug()<<"before sendto."<<name<<endl;
    sendto(udp_fd,buf.data(),buf.size(),0,(struct sockaddr*)&addr,sizeof(addr));
    qDebug()<<"after sendto."<<endl;
}

void *recv_thread(void *ptr)
{
    Chat *This=(Chat *)ptr;

    qDebug()<<"recv_thread works.";
    This->run();
    return NULL;
}


void Chat::run()
{
    while(1)
    {
        struct sockaddr_in addr;
        socklen_t len=sizeof(addr);
        char buf[4096];

        qDebug()<<"bfore recvfrom";
        int ret=recvfrom(udp_fd,buf,sizeof(buf),0,(struct sockaddr*)&addr,
                         &len);
        qDebug()<<"recvfrom works.";
        qDebug()<<"ret"<<ret;
        if(ret>0)
        {
            char *ip=inet_ntoa(addr.sin_addr);
            buf[ret]=0;
            qDebug()<<"recv buf is"<<buf<<"ip is "<<ip;
            QJsonDocument doc=QJsonDocument::fromJson(QByteArray(buf));
            QJsonObject obj=doc.object();//直接将qjsondocument转换为qjsonobject
            QString name=obj.value(NAME).toString();
            emit showip(name,ip);

            handleMsg(doc.object(),ip);
        }else if(ret<0&&errno!=EINTR)
        {
            qDebug()<<"errno recv";
            exit(2);
        }
    }
}

void Chat::init()
{
    this->udp_fd=socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(9988);
    addr.sin_addr.s_addr=inet_addr("0.0.0.0");
  //  addr.sin_addr.s_addr=inet_addr("192.168.19.101");
    int ret=bind(udp_fd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret!=0)
    {
        qDebug()<<"error bind";
        exit(1);
    }

    int arg=1;
    setsockopt(udp_fd,SOL_SOCKET,SO_BROADCAST,&arg,sizeof(arg));

    QJsonObject obj;
    obj.insert(CMD,ONLINE);
    obj.insert(NAME,name);


    send(obj,"255.255.255.255");
    pthread_create(&tid,NULL,recv_thread,this);

}

void Chat::handleMsg(const QJsonObject &obj,QString ip)
{
    if(ips.indexOf(ip)!=-1)
    {
        qDebug()<<"send message to self";
        return;
    }

    QString cmd=obj.value(CMD).toString();
    if(cmd==ONLINE)
    {
        QString name=obj.value(NAME).toString();
        addUser(ip,name);

        QJsonObject resp;
        resp.insert(CMD,ONLINEACK);
        resp.insert(NAME,name);
        send(resp,ip);

    }
    if(cmd==ONLINEACK)
    {
        QString name=obj.value(NAME).toString();
        addUser(ip,name);
    }

    if(cmd==CHAT)
    {
        bool broadcast=obj.value("255.255.255.255").toBool();
        QString content=obj.value(CONTENT).toString();
        QString name=obj.value(NAME).toString();
    qDebug()<<"before emit";
        emit this->sigNewContent(name,content,broadcast);
    qDebug()<<"after emit";
    }
}

void Chat::addUser(QString ip,QString name)
{
    User *user=new User;
    user->ip=ip;
    user->name=name;

    if(others[ip])delete others[ip];
    others[ip]=user;

    qDebug()<<"signal emit";
    emit sigNewUser(name,ip);
}

QStringList Chat::getSysIps()
{
    QStringList ret;
    QList<QNetworkAddressEntry>entrys;

    QList<QNetworkInterface>infs=QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface inf,infs)
    {
        entrys.append(inf.addressEntries());
    }

    foreach(QNetworkAddressEntry entry,entrys)
    {
        if(entry.ip().toString().length()!=0)
            ret.append(entry.ip().toString());
        ret.append(entry.ip().toString());
    }

    return ret;


}


QString Chat::getSysName()
{
    char buf[1024];
    memset(buf,0,sizeof(buf));
    FILE *fp=popen("whoami","r");
    int ret=fread(buf,1,sizeof(buf),fp);
    buf[ret-1]=0;
    fclose(fp);
    return QString(buf);
}
