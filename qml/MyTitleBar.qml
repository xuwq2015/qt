import QtQuick 2.0
import QtQuick.Controls 1.2

import "qrc:/top-levelWindow"
import "qrc:/button"

Rectangle {
    property bool windowStatus: false                //true = 正常， false = 最大化
    property string titleText                       //标题文本
    property string normal: "qrc:/image/normal_2.png"
    property string enter: "qrc:/image/normal_3.png"
    property string press: "qrc:/image/normal_1.png"

    signal closeWindow()                            //关闭窗口信号
    signal maxWindow()                              //最大化窗口
    signal minWindow()                              //最小化
    signal normalWindow()                           //正常


    Image {
        id: titleBackground
        anchors.fill: parent
        source: "qrc:/image/title_background.png"
    }
    TitleButton {   //关闭按钮
        id: closeButton
        width: 30
        height: 25
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 2

        normalPath: "qrc:/image/close_2.png"
        enterPath: "qrc:/image/close_3.png"
        pressPath: "qrc:/image/close_1.png"

        onButtonClick: closeWindow()
    }

    TitleButton {   //最大化按钮
        id: maxButton
        width: 30
        height: 25

        anchors.top: parent.top
        anchors.right: closeButton.left

        normalPath: normal
        enterPath: enter
        pressPath: press

        onButtonClick: sendSignal()
    }

    TitleButton {
        id: minButton
        width: 30
        height: 25

        anchors.top: parent.top
        anchors.right: maxButton.left

        normalPath: "qrc:/image/minWindow_2.png"
        enterPath: "qrc:/image/minWindow_3.png"
        pressPath: "qrc:/image/minWindow_1.png"

        onButtonClick: minWindow()
    }

    Rectangle {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: minButton.left
        color:Qt.rgba(0.5,0.5,0.5,0.0)
//        Image {
//            id: titleBackground
//            anchors.fill: parent
//            source: "qrc:/image/title_background.png"
//        }

        MouseArea {
            anchors.fill: parent
            property point clickPos: "0,0"
            onPressed: {
                clickPos  = Qt.point(mouse.x,mouse.y)
            }

            onPositionChanged: {
                //鼠标偏移量
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)

                //如果mainwindow继承自QWidget,用setPos
                mainWindow.setX(mainWindow.x+delta.x)
                mainWindow.setY(mainWindow.y+delta.y)
            }
        }

        Text {  //窗口标题
            anchors.left: parent.left
//            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 30
            text: qsTr(titleText)
            color: "#fffffb"
        }
    }

    /*
     *根据窗口此时的状态（最大化，正常），点击最大化按钮时发送相对应的信号（最大化，正常），
     *并改变按钮图标
     */
    function sendSignal() {
        if(windowStatus) {//将窗口最大化
            windowStatus = false    //改变窗口状态
            maxWindow()             //发送窗口最大化图标

            //重新加载窗口最大化后的最大化按钮图标F
            normal = "qrc:/image/normal_2.png"
            enter = "qrc:/image/normal_3.png"
            press = "qrc:/image/normal_1.png"
        } else { //将窗口正常化
            windowStatus = true
            normalWindow()
            normal = "qrc:/image/maxWindow_2.png"
            enter = "qrc:/image/maxWindow_3.png"
            press = "qrc:/image/maxWindow_1.png"
        }
    }
}
