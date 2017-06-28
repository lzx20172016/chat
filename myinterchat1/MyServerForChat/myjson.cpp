#include<QJsonObject>
#include<QString>
#include<QDebug>
struct Person
{
    QString name;
    int age;
    int salary;
};

int main(int argc,char *argv[])
{
    QJsonObject obj;
    obj.insert("name","xiaohong");
    obj.insert("age",12);
    obj.insert("salary",120);

    Person p;
    p.name=obj.value("name").toString();
    p.age=obj.value("age").toInt();
    p.salary=obj.value("salary").toInt();

    qDebug()<<"name="<<p.name<<endl;
    qDebug()<<"age="<<p.age<<endl;
    qDebug()<<"salary="<<p.salary<<endl;
    return 0;
}
