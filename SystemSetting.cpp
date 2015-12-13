/************************************************************
  Copyright (C), 2014-2015, Everyoo Tech. Co., Ltd.
  FileName: test.cpp
  Author:        Version :          Date:
  Description:     // 模块描述
  Version:         // 版本信息
  History:         // 历史修改记录
      <author>  <time>   <version >   <desc>
      David    2015/1/12     1.0     build this moudle
***********************************************************/

#include "SystemSetting.h"

SystemSetting::SystemSetting(QObject *parent) : QObject(parent) {
    saveUserNameStatus = false;
    saveUserPasswordStatus = false;

    QDir dir;
    if(dir.exists("./configuration/")) {
        //存在配置文件
        systemSetting = new QSettings("./configuration/systemSetting.ini", QSettings::IniFormat);
    } else {
        //初始化配置文件
        dir.mkpath("./configuration/");
        QSettings settings("./configuration/systemSetting.ini", QSettings::IniFormat); // 当前目录的INI文件
        settings.setValue("uplinkPort", 9901);
        settings.setValue("downlinkPort", 9900);
        settings.setValue("databaseType", "QMYSQL");
        settings.setValue("hostName", "192.168.100.166");
        settings.setValue("databasePort", 3306);
        settings.setValue("databaseName", "woms");
        settings.setValue("databaseUser", "root");
        settings.setValue("databasePasswd", "everyoo");
        systemSetting = new QSettings("./configuration/systemSetting.ini", QSettings::IniFormat);
    }
}

SystemSetting::~SystemSetting() {

}

QString SystemSetting::readSettings(QString parameters) {
    //读取系统设置
    return systemSetting->value(parameters).toString();
}

void SystemSetting::writeSettings(QString parameters, QString value) {
    //保存或修改系统设置
    systemSetting->setValue(parameters, value);
}


void SystemSetting::modifyUserSetting(QString user, QString key, QString value) {
    //修改用户配置或添加用户设置
    QString userFile("./configuration/");
    userFile.append(user);
    userFile.append(".ini");

    QSettings settings(userFile, QSettings::IniFormat);
    settings.setValue(key, value);
}

void SystemSetting::initUserSetting(QString user) {
    //初始化用户设置
    QString userFile("./configuration/");
    userFile.append(user);
    userFile.append(".ini");

    QSettings settings(userFile, QSettings::IniFormat);
    settings.setValue("userName", user);
    settings.setValue("savePassword", "0");
}

void SystemSetting::deleteUserSetting(QString user) {
    //删除用户设置
    QString userFile("./configuration/");
    userFile.append(user);
    userFile.append(".ini");

    QDir qdir;
    qdir.remove(userFile);
}

void SystemSetting::getSaveUser() {
    QDir dir("./configuration/");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList fileInfoList = dir.entryInfoList();
    if(!fileInfoList.isEmpty()) {
        for(int i = 0; i < fileInfoList.size() - 1 ; i++) {
            QFileInfo fileName(fileInfoList.at(i));
            if(fileName.fileName() != "systemSetting.ini") {
                setAddComboBoxItem(fileName.baseName());
            }
        }
    } else {
        setAddComboBoxItem("");
    }

    emit addComplete();
}

bool SystemSetting::getSavePassword(QString user) {
    //判断是否已保存密码,若已保存密码则返回true,否则返回false
    QString userFile("./configuration/");
    userFile.append(user);
    userFile.append(".ini");

    QSettings setting(userFile, QSettings::IniFormat);
    if(setting.value("savePassword").toInt())
        return true;
    else
        return false;
}

QString SystemSetting::getUserSetting(QString user, QString key) {
    QString userFile("./configuration/");
    userFile.append(user);
    userFile.append(".ini");

    QSettings setting(userFile, QSettings::IniFormat);
    return setting.value(key).toString();
}


bool SystemSetting::saveUserName() {
    return saveUserNameStatus;
}

void SystemSetting::setSaveUserName(bool status) {
    saveUserNameStatus = status;
}

bool SystemSetting::saveUserPassword() {
    return saveUserPasswordStatus;
}

void SystemSetting::setSaveUserPassword(bool status) {
    saveUserPasswordStatus = status;
}

QString SystemSetting::loginUserName() {
    return loginUser;
}

void SystemSetting::setLoginUserName(QString user) {
    loginUser = user;
}

QString SystemSetting::addComboBoxItem() {
    return addComboBox;
}

void SystemSetting::setAddComboBoxItem(QString item) {
    addComboBox = item;
    emit addComboBoxItemChanged();
}


void SystemSetting::saveLoginSetting() {
    if (saveUserName()) {
        if (saveUserPassword()) {
            modifyUserSetting(loginUserName(), "savePassword", "1");
        } else {
            initUserSetting(loginUserName());
        }
    } else {
        QString fileName("./configuration/");
        fileName.append(loginUserName());
        fileName.append(".ini");
        QFileInfo fileInfo(fileName);
        if (fileInfo.exists()) {
            QDir qdir;
            qdir.remove(fileName);
        }
    }
}

