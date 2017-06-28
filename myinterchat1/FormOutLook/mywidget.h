#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QListWidget>
#include<QTextBrowser>
#include<QTextEdit>
#include<QPushButton>
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    QListWidget *userList;
    QTextBrowser*msgShow;
    QTextEdit*msgInput;
    QPushButton *sendMsg;
    QPushButton *setup;
    QPushButton *sendFile;
    MyWidget(QWidget *parent = 0);
    ~MyWidget();
};

#endif // MYWIDGET_H
