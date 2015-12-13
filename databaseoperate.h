#ifndef DATABASEOPERATE_H
#define DATABASEOPERATE_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>

typedef struct db_info {
    QString dbType;         //数据库类型
    QString dbHostName;     //数据库主机
    QString dbPort;         //数据库服务器端口号
    QString dbName;         //数据库名
    QString dbUser;         //数据库用户名
    QString dbPasswd;       //数据库密码
}dbInfo;

class DatabaseOperate : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseOperate(dbInfo dbInfo_v, QObject *parent = 0);
    ~DatabaseOperate();

    void addUser();     //添加用户信息

public:
    QSqlDatabase db;

signals:

public slots:
};

#endif // DATABASEOPERATE_H
