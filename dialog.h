/*
 * ���ļ�������һ���ޱ߿򣬿��ƶ��Ĵ���,�����ƴ��ڱ���
 * */
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //������̳�
    virtual void paintEvent(QPaintEvent *event);
private:
    QPoint m_movePoint; //�ƶ��ľ���
    bool m_mousePress; //����������
};

#endif // DIALOG_H
