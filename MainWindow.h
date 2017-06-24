#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include<QListWidget>
#include<QTextEdit>
#include<QPushButton>
#include<QSplitter>
#include<QVBoxLayout>
#include<QTextBrowser>

#include "Chat.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    Chat chat;
    QListWidget *userList;
    QTextEdit*msgInput;
    QPushButton *sendMsg;
    QPushButton *setup;
    QTextBrowser *msgShow;
signals:

public slots:
    void onNewUser(QString name,QString ip);
};

#endif // MAINWINDOW_H
