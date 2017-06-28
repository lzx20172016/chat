#include<QDebug>


int main(int argc,char *argv[])
{
    FILE *fp=popen("whoami","r");

    char buf[4096];
    memset(buf,0,sizeof(buf));

    int ret=fread(buf,1,sizeof(buf),fp);
    buf[ret-1]=0;
    fclose(fp);
    qDebug()<<QString(buf);//qDebug() can not print char directly

}
