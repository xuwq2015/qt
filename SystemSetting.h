#ifndef _SYSTEM_SETTING_H_
#define _SYSTEM_SETTING_H_

#include <QObject>
#include <QSettings>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include "Utils.h"

class SystemSetting : public QObject {
    Q_OBJECT

    /*
     * 宏Q_PROPERTY用来向qml中注册一个变量，使用此宏可在qml中直接调用此变量。
     * Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)为宏的原型；
     * type name: 为变量，如：QString addComboBoxItem
     * READ name: 为读取变量的函数，在qml中使用此变量后会自动调用此函数，如：addComboBoxItem()
     * WRITE setName: 为变量赋值函数，在qml中为变量赋值后系统自动调用此函数，如：setAddComboBoxItem();
     * NOTIFY nameChanged: 为信号，可在qml中接收此信号，可根据实际情况发送此信号,如在调用setAddComboBoxItem()
     * 函数后；
     *
     * 注意：name变量的值必须用另一个变量来存储，不可以直接用此变量来存储。
    */
    Q_PROPERTY(bool saveUserName READ saveUserName WRITE setSaveUserName)
    Q_PROPERTY(bool saveUserPassword READ saveUserPassword WRITE setSaveUserPassword)
    Q_PROPERTY(QString loginUserName READ loginUserName WRITE setLoginUserName)
    Q_PROPERTY(QString addComboBoxItem READ addComboBoxItem WRITE setAddComboBoxItem NOTIFY addComboBoxItemChanged)

public:
    explicit SystemSetting(QObject *parent = 0);
    ~SystemSetting();

public:
    QSettings *systemSetting;
    bool saveUserNameStatus;
    bool saveUserPasswordStatus;
    QString loginUser;
    QString addComboBox;


public:

    /*
     * 宏Q_INVOKABLE用来向qml注册一个函数，使用此宏注册过的函数可在qml中直接调用。
     */
    Q_INVOKABLE QString readSettings(QString);
    Q_INVOKABLE void writeSettings(QString, QString);
    Q_INVOKABLE void modifyUserSetting(QString, QString, QString);  //修改或添加用户设置
    Q_INVOKABLE void initUserSetting(QString);                      //初始化用户设置
    Q_INVOKABLE void deleteUserSetting(QString);                    //删除用户设置
    Q_INVOKABLE void getSaveUser();
    Q_INVOKABLE bool getSavePassword(QString);                      //判断是否已保存密码
    Q_INVOKABLE QString getUserSetting(QString, QString);
    Q_INVOKABLE void saveLoginSetting();

    /*对注册到qml的变量提供读取操作*/
    bool saveUserName();
    void setSaveUserName(bool);

    bool saveUserPassword();
    void setSaveUserPassword(bool);

    QString loginUserName();
    void setLoginUserName(QString);

    QString addComboBoxItem();
    void setAddComboBoxItem(QString);

signals:
    void addComboBoxItemChanged();
    void addComplete();

public slots:

};

#endif // _SYSTEM_SETTING_H_
