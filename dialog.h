/*
 * 此文件创建了一个无边框，可移动的窗口,并绘制窗口背景
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
    //供子类继承
    virtual void paintEvent(QPaintEvent *event);
private:
    QPoint m_movePoint; //移动的距离
    bool m_mousePress; //按下鼠标左键
};

#endif // DIALOG_H
