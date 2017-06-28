#include "mywidget.h"
#include<QVBoxLayout>
MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
   // QVBoxLayout*m=new QVBoxLayout(this);//

  //  userList=new QListWidget;
  //  m->addWidget(userList);

    QVBoxLayout *vBox=new QVBoxLayout(this);
    msgShow=new QTextBrowser;
    vBox->addWidget(msgShow);
    msgInput=new QTextEdit;
    vBox->addWidget(msgInput);

    setup=new QPushButton("set");
    sendFile=new QPushButton("sendfile");
    sendMsg=new QPushButton("send");
    vBox->addWidget(setup);
    vBox->addWidget(sendFile);
    vBox->addWidget(sendMsg);


}

MyWidget::~MyWidget()
{

}
