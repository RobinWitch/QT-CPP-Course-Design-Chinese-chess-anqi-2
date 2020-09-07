#include "Board.h"
#include<QPainter>

Board::Board(QWidget *parent) : QWidget(parent)   //Board构造函数
{
    for(int i=0;i<32;i++)
    {
        _s[i].construct(i);//对每个棋子进行位置、颜色、死亡、是否翻面的初始化
    }
}
void Board::paintEvent(QPaintEvent*)      //画棋盘和棋子
{
    QPainter painter(this);

    int d=100;  //棋子直径
    _r=d/2;

    for(int i=1;i<=10;i++)  //画十条横线
    {
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }

    for(int i=1;i<=9;i++)   //画九条竖线
    {
        if(i==1||i==9)
            painter.drawLine(QPoint(d*i,d),QPoint(i*d,10*d));
        else
        {
            painter.drawLine(QPoint(d*i,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(d*i,6*d),QPoint(i*d,10*d));
        }
    }

    painter.drawLine(QPoint(d*4,d),QPoint(6*d,3*d));    //画九宫格
    painter.drawLine(QPoint(d*6,d),QPoint(4*d,3*d));
    painter.drawLine(QPoint(d*4,10*d),QPoint(6*d,8*d));
    painter.drawLine(QPoint(d*6,10*d),QPoint(4*d,8*d));


    for(int i=0;i<32;i++)   //画32个棋子
    {
        drawStone(painter,i);
    }
}

QPoint Board::center(int row,int col)   //根据行列求出对应方块（棋子）中心点坐标，以QPoint类型返回
{
    QPoint ret;
    ret.rx()=(col+1.5)*(_r)*2;
    ret.ry()=(row+1.5)*(_r)*2;
    return ret;
}
QPoint Board::center(int id)
{
    return center(_s[id]._row,_s[id]._col);
}

void Board::drawStone(QPainter &painter,int id)     //给每个棋子写字上色显字
{
    QPoint c=center(id);
    QRect rect=QRect(c.rx()-(_r),c.ry()-(_r),(_r)*2,(_r)*2);

    painter.setBrush(QBrush(QColor(255,255,0)));   //棋子背景颜色

        painter.drawEllipse(center(id),_r,_r);      //画圆
        if(_s[id]._side)
        {

            if(_s[id]._side)
                    painter.setPen(Qt::black);  //画黑色矩形框以承载字体

            if(_s[id]._red)
                painter.setPen(Qt::red);  //将黑色矩形框换为红色矩形框


                painter.setFont(QFont("system", _r, 700));  //字体

                painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
        }
}

bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    for(row=0;row<4;row++)
    {
        for(col=0;col<8;col++)
        {
            QPoint c=center(row,col);
            if(((pt.x()-c.x())*(pt.x()-c.x())+(pt.y()-c.y())*(pt.y()-c.y()))<(_r)*(_r))
                return true;
        }
    }
    return false;
}
void Board::mousePressEvent(QMouseEvent *ev)
{
    QPoint pt=ev->pos();
    int row,col,i,j;
    if(getRowCol(pt,row,col))
    {
        for(i=0;i<32;i++)
        {
            if(_s[i]._row==row&&_s[i]._col==col)
            {
                _s[i]._side++;
                break;
            }
        }
        update();//刷新界面

        for(j=0;j<32;j++)
            if(_s[j]._clicked)
                break;

        if(j==32&&(_s[i]._side>1))
            _s[i]._clicked=true;

        else if(_s[i]._side>1)
        {
            _s[j]._row=_s[i]._row;
            _s[j]._col=_s[i]._col;
            _s[j]._clicked=false;
            _s[i]._dead=true;
            update();
        }
        for(int i=0;i<32;i++)
        {
            if(_s[i]._dead)
            {
                _s[i]._row=i/8+5;
                _s[i]._col=i%8;
                update();
            }
        }


    }

}
