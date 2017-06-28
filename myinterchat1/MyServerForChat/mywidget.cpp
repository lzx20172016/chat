#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    // QVBoxLayout*m=new QVBoxLayout(this);//

    //  userList=new QListWidget;
    //  m->addWidget(userList);
    userList=new QListWidget;//正是由于QListWidget使得可以选中某个ip，并发送信息
    QVBoxLayout *vBox=new QVBoxLayout(this);
    vBox->setMargin(0);
    QSplitter *splitter=new QSplitter(this);//divide into two parts
    //vBox->addWidget(userList);

    splitter->addWidget(userList);
    vBox->addWidget(splitter);
    QWidget*contariner=new QWidget(this);
    splitter->addWidget(contariner);
    QVBoxLayout *vBoxr=new QVBoxLayout(contariner);
    vBoxr->setMargin(0);
    msgShow=new QTextBrowser;
    vBoxr->addWidget(msgShow);
    msgInput=new QTextEdit;
    vBoxr->addWidget(msgInput);
    QHBoxLayout *hBoxr=new QHBoxLayout;
    vBoxr->addLayout(hBoxr);

    setup=new QPushButton("set");
    sendFile=new QPushButton("sendfile");
    sendMsg=new QPushButton("send");
    hBoxr->addWidget(setup);
    hBoxr->addWidget(sendFile);
    hBoxr->addWidget(sendMsg);
    hBoxr->setMargin(0);
    chat.init();

    connect(&chat,SIGNAL(showip(QString,QString)),this,SLOT(onShowIp(QString,QString)));

    connect(sendMsg,SIGNAL(clicked()),this,SLOT(onSend()));
    connect(&chat,SIGNAL(sigNewContent(QString,QString,bool)),this,SLOT(showcontent(QString,QString,bool)));
}

MyWidget::~MyWidget()
{

}

void MyWidget::onShowIp(QString name,QString ip)
{
    userList->addItem(name+"@"+ip);
    userList->update();
}

void MyWidget::onSend()
{
    //获得当前qlistwidget中的鼠标点击的widget对象
    QString qlw=this->userList->currentItem()->text();
    qDebug()<<"qlw="<<qlw;

    //获得Ip,通过划分@的方式，将@左右两边的字符串存入QStringList中去
    QStringList nameip=qlw.split('@');

    QString ip=nameip.at(1);
    QString name1=nameip.at(0);
    qDebug()<<"name1"<<name1;
    QString content=msgInput->toPlainText();
    QJsonObject obj;
    obj.insert(CMD,CHAT);
    obj.insert(NAME,chat.name);
    obj.insert(CONTENT,content);

    //获得输入栏中的数据

    chat.send(obj,ip);

    msgInput->clear();//清除输入栏的数据

    msgShow->append("我说:"+content);//在展示栏中添加要打印的数据
}

void MyWidget::showcontent(QString name, QString content,bool b1)
{
    msgShow->append(name+"说:"+content);






}
