#ifndef MYCHAT_H
#define MYCHAT_H

#include <QObject>

class MyChat : public QObject
{
    Q_OBJECT
public:
    explicit MyChat(QObject *parent = 0);

signals:

public slots:
};

#endif // MYCHAT_H