/*
    此类用于创建一个新的tcp服务器，通过参数tcpPort指定的端口进行监听；
    在一个新的tcp连接进入后读取其中的传入的数据
*/
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(int tcpPort, QObject *parent = 0);

	QString getIP();
public:
    QTcpServer *tcpService;
    QTcpSocket *tcpSocket;
    QByteArray readData;    //从tcp连接中读取到的数据

signals:

public slots:
    void onNewConnection();     //有新的tcp连接请求
    void onReadyRead();         //有新的数据传入
signals:

public slots:
};

#endif // TCPSERVER_H
