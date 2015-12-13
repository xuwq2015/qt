/*
    此类用于创建一个新的tcp服务器，通过参数tcpPort指定的端口进行监听；
    在一个新的tcp连接进入后读取其中的传入的数据
*/
#include "tcpserver.h"

TcpServer::TcpServer(int tcpPort, QObject *parent) : QObject(parent){
    tcpService = new QTcpServer(this);  //创建tcp连接

    tcpService->listen(QHostAddress::Any,tcpPort);  //监听tcp连接

    /* 连接信号，当新的tcp连接进入后tcpServer发送此信号 */
    connect(tcpService, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

/* 获取新的tcp连接的套接字 */
void TcpServer::onNewConnection() {
    tcpSocket = tcpService->nextPendingConnection();

    /* 当次连接有数据传进来后会发送readyRead信号 */
    connect(this->tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

/* 开始读取tcp连接传进来的数据 */
void TcpServer::onReadyRead() {
    readData = tcpSocket->readAll();
}

QString TcpServer::getIP() { //返回服务器地址
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if(ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty()) {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
//    ipAddress = downlinkService->serverAddress().toString();
//    if(ipAddress.isNull()) {
//        qDebug()<<"ip地址为空";
//    }
    return ipAddress;
}