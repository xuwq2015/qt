#include "databaseoperate.h"

DatabaseOperate::DatabaseOperate(dbInfo dbInfo_v, QObject *parent) : QObject(parent) {
  db = QSqlDatabase::addDatabase(dbInfo_v.dbType);
  db.setHostName(dbInfo_v.dbHostName);
  db.setPort(dbInfo_v.dbPort);
  db.setDatabaseName(dbInfo_v.dbName);
  db.setUserName(dbInfo_v.dbUser);
  db.setPassword(dbInfo_v.dbPasswd);

  if (!(db.open())) {
      emit connectDatabaseError(db.lastError().text());
  }
}

DatabaseOperate::~DatabaseOperate() {
    db.close();
}

void DatabaseOperate::addUser() {
    QString userid = "0001";
    QString userName = "xwq";
    QString passwd = "123456";

    QSqlQuery query;
    /*添加用户信息*/
    query.prepare("INSERT INTO account(id, username, passwd) VALUES (?, ?, ?)");

    query.addBindValue(userid);
    query.addBindValue(userName);
    query.addBindValue(passwd);

    if (!query.exec()) {
        qDebug()<<query.lastError();
    }
}
