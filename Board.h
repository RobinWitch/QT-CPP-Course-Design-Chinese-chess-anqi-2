#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include"Stone.h"
#include<QMouseEvent>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    Stone _s[32];
    int _r;//棋子半径

    //返回棋盘对应的窗口坐标
    QPoint center(int row,int col);
    QPoint center(int id);

    void drawStone(QPainter &painter,int id);   //给棋子上色
    void paintEvent(QPaintEvent *);             //画棋盘
    bool getRowCol(QPoint pt,int &row,int &col);    //判断鼠标是否点击棋盘内，并且改变row。col
    void mousePressEvent(QMouseEvent *ev);

signals:

public slots:
};

#endif // BOARD_H
