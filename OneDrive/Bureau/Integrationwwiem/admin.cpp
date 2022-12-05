#include "admin.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QDate>
#include<QObject>

admin::admin()
{
  id=0;
  username="";
  password="";
  role="";
}
admin::admin(QString username,QString password,QString role)
{

    this->username=username;
    this->password=password;
    this->role=role;
}
bool admin::Login()
{
    QSqlQuery query;
       bool test=false;

           query.prepare("Select ADMIN,MDP,role FROM USER1 where ADMIN=:username and MDP=:password");
            query.bindValue(":username",username);
             query.bindValue(":password",password);
             query.bindValue(":role",role);

             if(query.exec()&&query.next())
       {
                 test=true;
            return test;
       }
       return test;
}
QString admin::afficherRole()
{
    QSqlQuery query;

           query.prepare("Select ADMIN,MDP,role FROM USER1 where ADMIN=:username and MDP=:password");
            query.bindValue(":username",username);
             query.bindValue(":password",password);
             query.bindValue(":role",role);
            query.exec();
            query.next();
            QString a=query.value(2).toString();


return a;
}
