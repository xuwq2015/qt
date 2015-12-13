#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QDir>


#include "ManageServer.h"
#include "ConnectDatabase.h"
#include "SystemSetting.h"
#include "SignIn.h"
#include "ConcentratorInfo.h"
#include "WindowsMachineInfo.h"
#include "OneTypeData.h"
#include "datastruct.h"

ConcentratorInfo* concentratorStruct;
ConnectDatabase* operateDatabase;
WindowsMachineInfo windowMachineInfo;
OneTypeData oneTypeData;
QList<concentratorCacheStruct> concentratorList;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //qmlRegisterType<ManageServer>("an.qt.ManageServer", 1, 0, "ManageServer");
    //qmlRegisterType<ConnectDatabase>("an.qt.ConnectDatabase", 1, 0, "ConnectDatabase");

    // 先实例化一个继承自QObject的实例
    SystemSetting *systemSetting = new SystemSetting(&app);
    operateDatabase = new ConnectDatabase(&app);
    ManageServer *manageServer = new ManageServer(&app);
    SignIn *signIn = new SignIn(operateDatabase, &app);
    concentratorStruct = new ConcentratorInfo();

    QQmlApplicationEngine engine;

    /*在将实例化后对象注册到qml引擎的运行环境中去
    下面的语句相当于向运行环境注册一个名为sendmessage的全局单例对象
     qmlRegisterSendMessage 这个函数使用比较复杂，就不会在此使用*/

    engine.rootContext()->setContextProperty("manageServer", manageServer);
    engine.rootContext()->setContextProperty("operateDatabase", operateDatabase);
    engine.rootContext()->setContextProperty("modifySettings", systemSetting);
    engine.rootContext()->setContextProperty("signInCpp", signIn);
    engine.rootContext()->setContextProperty("concentratorStruct", concentratorStruct);
    engine.rootContext()->setContextProperty("windowMachineInfo",&windowMachineInfo);
    engine.rootContext()->setContextProperty("oneTypeData", &oneTypeData);

    QApplication::addLibraryPath("./");
    engine.load(QUrl(QStringLiteral("qrc:/top-levelWindow/SignIn.qml")));
    signIn->initSignIn();


    return app.exec();
}
