#include<QDebug>
#include<QJsonObject>
#include<QString>
#include<QByteArray>
#include<QJsonDocument>

struct Person
{
    QString name;
    int age;
    int salary;
};

int main1(int argc,char *argv[])
{
    QJsonObject obj;
    obj.insert("name:","lihua");
    obj.insert("age:",20);
    obj.insert("salary:",100);

    Person p1;
    p1.name=obj.value("name:").toString();
    p1.age=obj.value("age:").toInt();
    p1.salary=obj.value("salary:").toInt();

    QJsonDocument jd(obj);
    QByteArray qba=jd.toJson();//form the data that is needed
    
    //-------------------------------------------------------------//  
    QJsonDocument jb=QJsonDocument::fromJson(qba);//form the QJsonDocument by QByteArray Datas
    QJsonObject obj1=jb.object();//form a new QJsonObject;
    Person p2;
    p2.name=obj1.value("name:").toString();
    p2.age=obj1.value("age:").toInt();
    p2.salary=obj1.value("salary:").toInt();

    qDebug()<<p2.name<<endl;
    qDebug()<<p2.age<<endl;
    qDebug()<<p2.salary<<endl;






    return 0;
}
