#include "dialog.h"
#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>

Dialog::Dialog(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setObjectName("basewidget");
}

Dialog::~Dialog()
{

}
void Dialog::paintEvent(QPaintEvent *) {
QPainter painter(this);
    painter.setBrush(Qt::blue);		//设置画刷颜色
    painter.drawRect(0, 0, 900, 100);	//绘制矩形
}
void Dialog::mousePressEvent(QMouseEvent *event)
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        m_mousePress = true;
    }
    //窗口移动距离
    m_movePoint = event->globalPos() - pos();
}

void Dialog::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePress = false;
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(m_mousePress)
    {
        QPoint movePpos = event->globalPos();
        move(movePpos - m_movePoint);
    }
}
