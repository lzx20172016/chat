#include<QDebug>


int main(int argc,char *argv[])
{
    FILE *fp1=popen("whoami","r");

    char buf[4096];
    memset(buf,0,sizeof(buf));

    int ret=fread(buf,1,sizeof(buf),fp1);
    buf[ret-1]=0;
    fclose(fp1);
    qDebug()<<QString(buf);

}
