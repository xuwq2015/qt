import QtQuick 2.0

import "qrc:/top-levelWindow"
import "qrc:/boolBar"

/*自定义功能栏按钮*/
Rectangle {
    radius: 5      //设置圆角半径

    property string iconPath                         //按钮图标路径
    property string iconText                         //图标文本
    property bool functionButtonMouseAreaEvent:true  //是否处理鼠标事件
    property bool mouseClickEvent: true              //是否处理鼠标点击事件

    signal buttonClick()                             //鼠标点击时发送此信号

    color:Qt.rgba(0.5,0.5,0.5,0.0)

    opacity: 1                                       //设置按钮透明度

    Image {                                          //添加按钮图标
        id: background
        anchors.top: parent.top
        anchors.bottom: buttonText.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 8
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 8
        source: iconPath
    }

    Text {  //设置图标文本
        id: buttonText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        text: qsTr(iconText)
        font.pixelSize: 14
        font.family: "宋体"
        font.bold: true
        color: "#ecf0f1"
    }

    MouseArea { //处理鼠标事件
        enabled: functionButtonMouseAreaEvent
        anchors.fill: parent
        hoverEnabled: true                  //处理没有按下时的鼠标事件
        onClicked: {                        //点击按钮时发送buttonClick信号
            //判断是否处理鼠标点击
            if(mouseClickEvent)
                buttonClick()
        }
        onEntered: setColor(1)              //鼠标进入按钮区
        onPressed: setColor(2)              //鼠标按下
        onExited: setColor(0)               //鼠标离开按钮区
        onReleased: setColor(1)             //鼠标释放
    }

    function setColor(mouseStatus) {    //改变按钮颜色
        if(mouseStatus === 0) {         //鼠标退出和释放后的颜色
            color = Qt.rgba(0.5,0.5,0.5,0.0)
        } else if(mouseStatus === 1) {    //鼠标进入按钮区域时的颜色
            color = Qt.rgba(0.5,0.5,0.5,0.5)
        } else if(mouseStatus === 2) {   //鼠标按下时的颜色
            color = Qt.rgba(0.5,0.5,0.5,0.9)
        }
    }
}


