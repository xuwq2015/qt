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
    painter.setBrush(Qt::blue);		//���û�ˢ��ɫ
    painter.drawRect(0, 0, 900, 100);	//���ƾ���
}
void Dialog::mousePressEvent(QMouseEvent *event)
{
    //ֻ�����������ƶ��͸ı��С
    if(event->button() == Qt::LeftButton)
    {
        m_mousePress = true;
    }
    //�����ƶ�����
    m_movePoint = event->globalPos() - pos();
}

void Dialog::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePress = false;
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    //�ƶ�����
    if(m_mousePress)
    {
        QPoint movePpos = event->globalPos();
        move(movePpos - m_movePoint);
    }
}
